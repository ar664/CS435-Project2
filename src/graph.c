#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void AddNode(Graph* graph, char* val);
void AddUndirectedEdge(Graph* graph, Node* first, Node* second);
void RemoveUndirectedEdge(Graph* graph, Node* first, Node* second);
GHashTable* GetAllNodes(Graph* graph);

Graph* GraphAllocate()
{
    Graph* graph = malloc(sizeof(Graph));

    graph->AddNode = AddNode;
    graph->AddUndirectedEdge = AddUndirectedEdge;
    graph->RemoveUndirectedEdge = RemoveUndirectedEdge;
    graph->GetAllNodes = GetAllNodes;

    graph->nodehash = g_hash_table_new(g_str_hash, g_str_equal);
    graph->nodes = malloc(GRAPH_NODE_ALLOC_INC*sizeof(Node*));
    graph->nodeCount = 0;

    return NULL;
}

void AddNode(Graph* graph, char* val)
{
    Node* node;
    if(graph == NULL || val == NULL)
    {
        printf("AddNode: Attempted to add node with value %p to graph %p.\n", val, graph);
        return;
    }
    
    if(graph->nodeCount != 0 && (graph->nodeCount%GRAPH_NODE_ALLOC_INC) == 0)
    {
        graph->nodes = realloc(graph->nodes, (graph->nodeCount+GRAPH_NODE_ALLOC_INC)*sizeof(Node*));
    }

    node = NodeAllocate(val);
    graph->nodes[graph->nodeCount] = node;
    g_hash_table_insert(graph->nodehash, val, graph->nodes[graph->nodeCount]);
    graph->nodeCount++;
}

void AddUndirectedEdge(Graph* graph, Node* first, Node* second)
{
    if(graph == NULL || first == NULL || second == NULL)
    {
        printf("AddUndirectedEdge: Attempted to add edge to node %p and node %p.\nIn Graph %p.\n", first, second, graph);
        return;
    }

    NodeAddNeighbor(first, second);
    NodeAddNeighbor(second, first);
}

void RemoveUndirectedEdge(Graph* graph, Node* first, Node* second)
{
    if(graph == NULL || first == NULL || second == NULL)
    {
        printf("RemoveUndirectedEdge: Attempted to add edge to node %p and node %p.\nIn Graph %p.\n", first, second, graph);
        return;
    }

    NodeRemoveNeighbor(first, second);
    NodeRemoveNeighbor(second, first);
}

GHashTable* GetAllNodes(Graph* graph)
{
    if(graph == NULL)
    {
        printf("GetAllNodes: Attempted to get nodes from graph %p.\n", graph);
        return NULL;
    }
    return graph->nodehash;
}