#ifndef __GRAPH_H
#define __GRAPH_H

#include <glib.h>
#include "node.h"

typedef struct _Graph Graph;

struct _Graph
{
    Node**          nodes;
    int             nodeCount;
    GHashTable*     nodehash;
    GHashTable*     (*GetAllNodes)(Graph* graph);
    void            (*AddNode)(Graph* graph, char* val);
    void            (*AddUndirectedEdge)(Graph* graph, Node* first, Node* second);
    void            (*RemoveUndirectedEdge)(Graph* graph, Node* first, Node* second);
};

//The amount to allocate at first, then allocate more if needed
#define GRAPH_NODE_ALLOC_INC 1000

Graph* GraphAllocate();

#endif