//
// Created by sparkai on 22-11-7.
//

#ifndef CDATASTRUCTS_GRAPH_H
#define CDATASTRUCTS_GRAPH_H

#include "common.h"
typedef struct __Vector vector;
typedef struct __HashMap hashmap;
typedef struct __AdjList adj_list;

typedef struct __GNode {
    size_t id;
    void *data;
    adj_list *adj;
} gVertex;

typedef struct __Edge {
    size_t fromId;
    size_t toId;
    double weight;
} gEdge;


typedef struct __AdjList {
    size_t id;      // outgoing node
    double weight;
    adj_list *next;
} adj_list;

typedef struct __Graph {
    vector *vex_lst;
    vector *edge_lst;
    hashmap *vex_map;

    size_t elemSize;
    size_t num_vex;
    size_t num_edge;
    double *adj_mat;

    FreeFunction freeFn;
} graph;


void graphInit(graph* this, size_t elemSize, FreeFunction freeFn);
void graphDestroy(graph *this);
void graphPrepareMatrix(graph *this);
void graphPrint(graph *this);
void graphAddVertex(graph *this, size_t vexId, void *valueAddr);
void graphAddEdge(graph *this, size_t srcIdx, size_t dstIdx, double weight);


#endif //CDATASTRUCTS_GRAPH_H
