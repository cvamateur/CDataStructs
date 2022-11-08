//
// Created by sparkai on 22-11-7.
//

#ifndef CDATASTRUCTS_GRAPH_H
#define CDATASTRUCTS_GRAPH_H

#include "common.h"
typedef struct __Vector vector;
typedef struct __HashMap hashmap;
typedef struct __AdjNode adj_list;

typedef struct __GNode {
    size_t id;
    void *data;
} gVertex;

typedef struct __AdjNode {
    size_t id;      // outgoing node
    double weight;
    adj_list *next;
} adj_list;

typedef struct __Graph {
    vector *vex_lst;     // Array of vertexes
    hashmap *vex_map;    // Mapping from vexId to vexIdx in vex_lst

    size_t elemSize;
    size_t num_vex;
    size_t num_edge;

    double *adj_mat;    // Adjacent Matrix
    vector *adj_lst;    // Adjacent List

    FreeFunction freeFn;
} graph;


void graphInit(graph* this, size_t elemSize, FreeFunction freeFn);
void graphDestroy(graph *this);
void graphPrepareMatrix(graph *this);
void graphPrint(graph *this);
void graphAddVertex(graph *this, size_t vexId, void *valueAddr);
void graphAddEdge(graph *this, size_t srcIdx, size_t dstIdx, double weight);
void graphDFS(graph *this, MapFunction mapFn, void *auxData);

#endif //CDATASTRUCTS_GRAPH_H
