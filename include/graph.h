#ifndef __GRAPH_H
#define __GRAPH_H

#include "node.h"

typedef enum
{
    UNDIRECTED          = 0x1,
    DIRECTED            = 0x2,
    WEIGHTED            = 0x4,
    GRID                = 0x8
}GraphType;

typedef struct _Graph Graph;

struct _Graph
{
    int             type;
    Node**          nodes;
    int             nodeCount;
    GHashTable*     nodehash;
    GHashTable*     (*GetAllNodes)(Graph* graph);
    void            (*AddNode)(Graph* graph, char* val);
    void            (*AddGridNode)(Graph* graph, char* val, Vec2 position);
    void            (*AddUndirectedEdge)(Graph* graph, Node* first, Node* second);
    void            (*RemoveUndirectedEdge)(Graph* graph, Node* first, Node* second);
    void            (*AddDirectedEdge)(Graph* graph, Node* first, Node* second);
    void            (*RemoveDirectedEdge)(Graph* graph, Node* first, Node* second);
    void            (*AddWeightedEdge)(Graph* graph, Node* first, Node* second, int weight);
    void            (*RemoveWeightedEdge)(Graph* graph, Node* firts, Node* second);
};

//The amount to allocate at first, then allocate more if needed
#define GRAPH_NODE_ALLOC_INC 1000

Graph* GraphAllocate(int type);

Graph* CreateRandomUnweightedGraphIter(int n);

Graph* CreateLinkedList(int n);

Graph* CreateRandomDAGIter(int n);

Graph* CreateRandomCompleteWeightedGraph(int n);

Graph* CreateWeightedLinkedList(int n);

Graph* CreateRandomGridGraph(int n);

void GraphClearVisits(Graph* graph);

#endif