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
    newVex->id= id;
    newVex->adj = NULL;
    newVex->data = malloc(elemSize);
    memcpy(newVex->data, valueAddr, elemSize);
    return newVex;
}

static void freeVertex(void * vp) {
    gVertex *v = *(gVertex**) vp;
    adj_list *adj = v->adj;
    adj_list *trash;
    while (adj != NULL) {
        trash = adj;
        adj = adj->next;
        free(trash);
    }
    free(v);
}

static void freeEdge(void *vp) {
    gEdge *e = *(gEdge **) vp;
    free(e);
}

void graphInit(graph* this, size_t elemSize, FreeFunction freeFn) {
    this->vex_lst = NULL;
    this->vex_map = NULL;
    this->edge_lst = NULL;
    this->num_vex = 0;
    this->num_edge = 0;
    this->elemSize = elemSize;
    this->freeFn = freeFn;
    this->adj_mat = NULL;
}

void graphDestroy(graph *this) {
    if (this->vex_lst != NULL) {
        vectorDestroy(this->vex_lst);
        free(this->vex_lst);
        this->vex_lst = NULL;
    }
    if (this->edge_lst != NULL) {
        vectorDestroy(this->edge_lst);
        free(this->edge_lst);
        this->edge_lst = NULL;
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
}

void graphPrepareMatrix(graph *this) {
    if (this->adj_mat != NULL)
        free(this->adj_mat);

    // Allocate adjacent matrix
    size_t r = this->num_vex;
    size_t c = this->num_vex;
    this->adj_mat = malloc(r * c * sizeof(double));
    double *ptr = this->adj_mat;
    for (size_t i = 0; i < r; ++i) {
        for (size_t j = 0; j < c; ++j)
            *ptr++ = NAN;
    }

    // Create adjacent matrix and adjacent list
    size_t dstIdx;
    gVertex *vex;
    adj_list *adjLst;

    for (size_t i = 0; i < this->vex_lst->size; ++i) {
        vectorGet(this->vex_lst, i, &vex);
        adjLst = vex->adj;
        while (adjLst != NULL) {
            hashmapGet(this->vex_map, &adjLst->id, &dstIdx, REF_LONGLONG(-1));
            if (dstIdx == -1) {
                fprintf(stderr, "error: graph has invalid vertex-%zu\n", adjLst->id);
                exit(-1);
            }
            this->adj_mat[i * this->num_vex + dstIdx] = adjLst->weight;
            adjLst = adjLst->next;
        }
    }
    /*
    size_t fIdx, tIdx;
    gEdge *edge;
    for (size_t i = 0; i < this->num_edge; ++i) {
        vectorGet(this->edge_lst, i, &edge);
        hashmapGet(this->vex_map, &edge->fromId, &fIdx, REF_LONGLONG(-1));
        hashmapGet(this->vex_map, &edge->toId, &tIdx, REF_LONGLONG(-1));
        if (fIdx == -1) {
            fprintf(stderr, "error: graph has invalid vertex-%zu\n", fIdx);
            exit(-1);
        }
        if (tIdx == -1) {
            fprintf(stderr, "error: graph has invalid vertex-%zu\n", tIdx);
            exit(-1);
        }
        ptr[fIdx * c + tIdx] = edge->weight;
    }*/
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
        vectorInit(this->vex_lst, sizeof(gVertex*), 0, freeVertex);
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
        ++this->num_vex;
    }
}

void graphAddEdge(graph *this, size_t srcIdx, size_t dstIdx, double weight) {
    if (this->edge_lst == NULL) {
        this->edge_lst = malloc(sizeof(vector));
        vectorInit(this->edge_lst, sizeof(gEdge*), 0, freeEdge);
    }

    size_t fIdx, tIdx;
    gEdge *newEdge;
    gVertex *srcVex;
    adj_list *newAdj;

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

    // add edge to list
    newEdge = malloc(sizeof(gEdge));
    newEdge->fromId = srcIdx;
    newEdge->toId = dstIdx;
    newEdge->weight = weight;
    vectorPushBack(this->edge_lst, &newEdge);
    ++this->num_edge;

    // Add dstIdx to srcNode's adjList
    vectorGet(this->vex_lst, fIdx, &srcVex);
    newAdj = malloc(sizeof(adj_list));
    newAdj->id = dstIdx;
    newAdj->weight = weight;
    newAdj->next = srcVex->adj;
    srcVex->adj = newAdj;
}