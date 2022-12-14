//
// Created by sparkai on 22-11-7.
//
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include "graph.h"
#include "vector.h"
#include "hashmap.h"

#define NAN  DBL_MAX

static inline gVertex *gVertexNew(size_t id, void *valueAddr, size_t elemSize) {
    gVertex *newVex = malloc(sizeof(gVertex));
    newVex->id = id;
    newVex->data = malloc(elemSize);
    memcpy(newVex->data, valueAddr, elemSize);
    return newVex;
}

static void freeVertex(void *vp) {
    gVertex *v = *(gVertex **) vp;
    free(v);
}

static void freeAdjList(void *vp) {
    adj_list *trash;
    adj_list *adj = *(adj_list **) vp;
    while (adj != NULL) {
        trash = adj;
        adj = adj->next;
        free(trash);
    }
}

static void MapAdjacentMatrix(void *vp, size_t srcIdx, void *auxData) {
    adj_list *adj;
    size_t dstIdx;
    graph *g = auxData;
    vectorGet(g->adj_lst, srcIdx, &adj);
    while (adj != NULL) {
        hashmapGet(g->vex_map, &adj->id, &dstIdx, REF_LONGLONG(-1));
        if (dstIdx == -1) {
            fprintf(stderr, "error: graph has invalid vertex-%zu\n", adj->id);
            exit(-1);
        }
        g->adj_mat[srcIdx * g->num_vex + dstIdx] = adj->weight;
        adj = adj->next;
    }
}

void graphInit(graph *this, size_t elemSize, FreeFunction freeFn) {
    this->vex_lst = NULL;
    this->vex_map = NULL;
    this->num_vex = 0;
    this->num_edge = 0;
    this->elemSize = elemSize;
    this->freeFn = freeFn;
    this->adj_mat = NULL;
    this->adj_lst = NULL;
}

void graphDestroy(graph *this) {
    if (this->vex_lst != NULL) {
        vectorDestroy(this->vex_lst);
        free(this->vex_lst);
        this->vex_lst = NULL;
    }
    if (this->vex_map != NULL) {
        hashmapDestroy(this->vex_map);
        free(this->vex_map);
        this->vex_map = NULL;
    }
    if (this->adj_mat != NULL) {
        free(this->adj_mat);
        this->adj_mat = NULL;
    }
    if (this->adj_lst != NULL) {
        vectorDestroy(this->adj_lst);
        free(this->adj_lst);
        this->adj_lst = NULL;
    }
}

void graphPrepareMatrix(graph *this) {
    if (this->adj_mat != NULL)
        free(this->adj_mat);

    // Allocate adjacent matrix
    this->adj_mat = malloc(this->num_vex * this->num_vex * sizeof(double));
    double *ptr = this->adj_mat;
    for (size_t i = 0; i < this->num_vex; ++i) {
        for (size_t j = 0; j < this->num_vex; ++j)
            *ptr++ = NAN;
    }

    // Create adjacent matrix and adjacent list
    vectorMap2(this->vex_lst, MapAdjacentMatrix, this);
}

void graphPrint(graph *this) {
    if (this == NULL)
        return;

    gVertex *srcNode;
    gVertex *dstNode;
    double weight;
    if (this->adj_mat != NULL) {
        for (size_t i = 0; i < this->num_vex; ++i) {
            vectorGet(this->vex_lst, i, &srcNode);
            printf("%zu: ", srcNode->id);
            for (size_t j = 0; j < this->num_vex; ++j) {
                vectorGet(this->vex_lst, j, &dstNode);
                weight = this->adj_mat[i * this->num_vex + j];
                if (weight != NAN) {
                    printf("(%zu --%g--> %zu) ", srcNode->id, weight, dstNode->id);
                }
            }
            printf("\n");
        }
    }
}

void graphAddVertex(graph *this, size_t vexId, void *valueAddr) {
    if (this->vex_lst == NULL) {
        this->vex_lst = malloc(sizeof(vector));
        vectorInit(this->vex_lst, sizeof(gVertex *), 0, freeVertex);
    }
    if (this->vex_map == NULL) {
        this->vex_map = malloc(sizeof(hashmap));

#if ULONG_MAX == ULLONG_MAX
        hashmapInit(this->vex_map, sizeof(size_t), sizeof(size_t),
                    hashLongLong, LongLongEqual, NULL, NULL);
#else
        hashmapInit(this->vex_map, sizeof(size_t), sizeof(size_t),
                    hashLong, LongEqual, NULL, NULL);
#endif
    }
    if (this->adj_lst == NULL) {
        this->adj_lst = malloc(sizeof(vector));
        vectorInit(this->adj_lst, sizeof(adj_list *), 0, freeAdjList);
    }

    // if vexId exist
    size_t existIdx;
    gVertex *vex;
    hashmapGet(this->vex_map, &vexId, &existIdx, REF_LONGLONG(-1));
    if (existIdx == vexId) {
        vex = vectorNth(this->vex_lst, existIdx);
        if (this->freeFn != NULL)
            this->freeFn(vex->data);
        memcpy(vex->data, valueAddr, this->elemSize);

        // vexId is new
    } else {
        vex = gVertexNew(vexId, valueAddr, this->elemSize);
        vectorPushBack(this->vex_lst, &vex);
        hashmapSet(this->vex_map, &vexId, &this->num_vex);
        adj_list *emptyAdj = NULL;
        vectorPushBack(this->adj_lst, &emptyAdj);
        ++this->num_vex;
    }
}

void graphAddEdge(graph *this, size_t srcIdx, size_t dstIdx, double weight) {
    size_t fIdx, tIdx;
    adj_list *srcVexAdj;

    // check node validity
    hashmapGet(this->vex_map, &srcIdx, &fIdx, REF_LONGLONG(-1));
    hashmapGet(this->vex_map, &dstIdx, &tIdx, REF_LONGLONG(-1));
    if (fIdx == -1) {
        fprintf(stderr, "error: graph has invalid vertex-%zu\n", fIdx);
        exit(-1);
    }
    if (tIdx == -1) {
        fprintf(stderr, "error: graph has invalid vertex-%zu\n", tIdx);
        exit(-1);
    }

    // add to adj_list
    vectorGet(this->adj_lst, fIdx, &srcVexAdj);
    adj_list *newAdj = malloc(sizeof(adj_list));
    newAdj->id = dstIdx;
    newAdj->next = srcVexAdj;
    newAdj->weight = weight;
    vectorSet(this->adj_lst, fIdx, &newAdj);

    ++this->num_edge;
}

static void DFS_helper(gVertex *vex, size_t idx, MapFunction mapFn, void *auxData);


void graphDFS(graph *this, MapFunction mapFn, void *auxData) {

}