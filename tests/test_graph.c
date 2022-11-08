//
// Created by sparkai on 22-11-8.
//
#include "graph.h"


int main() {
    graph g;

    graphInit(&g, sizeof(double), NULL);

    graphAddVertex(&g, 1, REF_DOUBLE(10));
    graphAddVertex(&g, 5, REF_DOUBLE(50));
    graphAddVertex(&g, 3, REF_DOUBLE(30));
    graphAddVertex(&g, 4, REF_DOUBLE(40));
    graphAddVertex(&g, 2, REF_DOUBLE(20));

    graphAddEdge(&g, 1, 3, 1);
    graphAddEdge(&g, 2, 3, 1);
    graphAddEdge(&g, 3, 4, 2);
    graphAddEdge(&g, 4, 5, 2);
    graphAddEdge(&g, 1, 5, 0.5);

    graphPrepare(&g);

    graphPrint(&g);

    graphDestroy(&g);
}