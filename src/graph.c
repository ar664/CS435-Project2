#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "graph.h"

void AddNode(Graph* graph, char* val);
void AddGridNode(Graph* graph, char* val, Vec2 position);
void AddUndirectedEdge(Graph* graph, Node* first, Node* second);
void RemoveUndirectedEdge(Graph* graph, Node* first, Node* second);
void AddDirectedEdge(Graph* graph, Node* first, Node* second);
void RemoveDirectedEdge(Graph* graph, Node* first, Node* second);
void AddWeightedEdge(Graph* graph, Node* first, Node* second, int weight);
void RemoveWeightedEdge(Graph* graph, Node* first, Node* second);
GHashTable* GetAllNodes(Graph* graph);

Graph* GraphAllocate(int type)
{
    Graph* graph = calloc(1, sizeof(Graph));

    
    graph->type = type;

    if(type & (UNDIRECTED | GRID))
    {
        graph->AddUndirectedEdge = AddUndirectedEdge;
        graph->RemoveUndirectedEdge = RemoveUndirectedEdge;
    } 
    else if(type & DIRECTED)
    {
        graph->AddDirectedEdge = AddDirectedEdge;
        graph->RemoveDirectedEdge = RemoveDirectedEdge;
    }
    else if(type & WEIGHTED)
    {
        graph->AddWeightedEdge = AddWeightedEdge;
        graph->RemoveWeightedEdge = RemoveWeightedEdge;
    }
    
    graph->GetAllNodes = GetAllNodes;

    if(graph->type & GRID)
    {
        graph->AddGridNode = AddGridNode;
        //Get hash via Vec2
        graph->nodehash = g_hash_table_new_full(g_direct_hash, g_direct_equal, NULL, NULL);
    }
    else
    {
        graph->AddNode = AddNode;
        graph->nodehash = g_hash_table_new(g_str_hash, g_str_equal);
    }
    
    

    graph->nodes = malloc(GRAPH_NODE_ALLOC_INC*sizeof(Node*));
    graph->nodeCount = 0;

    return graph;
}

void AddNode(Graph* graph, char* val)
{
    Node* node;
    Vec2 placeholderPosition = {0};
    if(graph == NULL || val == NULL)
    {
        printf("AddNode: Attempted to add node with value %p to graph %p.\n", val, graph);
        return;
    }
    
    if(graph->nodeCount != 0 && (graph->nodeCount%GRAPH_NODE_ALLOC_INC) == 0)
    {
        graph->nodes = realloc(graph->nodes, (graph->nodeCount+GRAPH_NODE_ALLOC_INC)*sizeof(Node*));
    }

    node = NodeAllocate(val, placeholderPosition);
    graph->nodes[graph->nodeCount] = node;
    g_hash_table_insert(graph->nodehash, val, graph->nodes[graph->nodeCount]);
    graph->nodeCount++;
}

void AddGridNode(Graph* graph, char* val, Vec2 position)
{
    Node* node;
    u_int64_t key;
    if(graph == NULL || val == NULL)
    {
        printf("AddNode: Attempted to add node with value %p to graph %p.\n", val, graph);
        return;
    }
    
    if(graph->nodeCount != 0 && (graph->nodeCount%GRAPH_NODE_ALLOC_INC) == 0)
    {
        graph->nodes = realloc(graph->nodes, (graph->nodeCount+GRAPH_NODE_ALLOC_INC)*sizeof(Node*));
    }

    node = NodeAllocate(val, position);
    graph->nodes[graph->nodeCount] = node;

    key = GetVec2Key(node->position);
    g_hash_table_insert(graph->nodehash, (gpointer) GetVec2Key(node->position), graph->nodes[graph->nodeCount]);
    graph->nodeCount++;
}

void AddUndirectedEdge(Graph* graph, Node* first, Node* second)
{
    if(graph == NULL || first == NULL || second == NULL)
    {
        printf("AddUndirectedEdge: Attempted to add edge to node %p and node %p.\nIn Graph %p.\n", first, second, graph);
        return;
    }

    if(graph->type & GRID)
    {
        if(!NodeIsGridNeighbor(first->position, second->position))
        {
            return;
        }
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

void AddDirectedEdge(Graph* graph, Node* first, Node* second)
{
    if(graph == NULL || first == NULL || second == NULL)
    {
        printf("AddDirectedEdge: Attempted to add edge to node %p and node %p.\nIn Graph %p.\n", first, second, graph);
        return;
    }

    NodeAddNeighbor(first, second);
}

void RemoveDirectedEdge(Graph* graph, Node* first, Node* second)
{
    if(graph == NULL || first == NULL || second == NULL)
    {
        printf("RemoveDirectedEdge: Attempted to add edge to node %p and node %p.\nIn Graph %p.\n", first, second, graph);
        return;
    }

    NodeRemoveNeighbor(first, second);
}

void AddWeightedEdge(Graph* graph, Node* first, Node* second, int weight)
{
    if(graph == NULL || first == NULL || second == NULL)
    {
        printf("AddWeightedEdge: Attempted to add edge to node %p and node %p.\nIn Graph %p.\n", first, second, graph);
        return;
    }

    NodeAddWeightedNeighbor(first, second, weight);
}

void RemoveWeightedEdge(Graph* graph, Node* first, Node* second)
{
    if(graph == NULL || first == NULL || second == NULL)
    {
        printf("RemoveWeightedEdge: Attempted to add edge to node %p and node %p.\nIn Graph %p.\n", first, second, graph);
        return;
    }

    NodeRemoveWeightedNeighbor(first, second);
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

void GraphClearVisits(Graph* graph)
{
    int i;
    for(i = 0; i < graph->nodeCount; i++)
    {
        graph->nodes[i]->visited = 0;
    }
}

Graph* CreateRandomUnweightedGraphIter(int n)
{
	Graph* graph = GraphAllocate(UNDIRECTED);
	Node* nodeA, *nodeB;
	int i, length, edgeNum, randVal;
	char *nodeValue;
	
	edgeNum = n + rand()%n;

	for(i = 0; i < n; i++)
	{
		length = (int) log10(i+1) + 2;
		nodeValue = malloc(length*(sizeof(char)));
		sprintf(nodeValue, "%d", i);
		graph->AddNode(graph, nodeValue);
	}

	for(i = 0; i < edgeNum; i++)
	{
		randVal = rand()%n;
		nodeA = graph->nodes[randVal];
		randVal = rand()%n;
		while(graph->nodes[randVal] != nodeA && NodeConnectedUndirected( nodeA, graph->nodes[randVal]) )
		{
			randVal = rand()%n;
		}
		nodeB = graph->nodes[randVal];
		graph->AddUndirectedEdge(graph, nodeA, nodeB);
	}

	return graph;
}

Graph* CreateLinkedList(int n)
{
	Graph* graph = GraphAllocate(UNDIRECTED);
	int i, length;
	char* nodeValue;

	for(i = 0; i < n; i++)
	{
		length = (int) log10(i+1) + 2;
		nodeValue = malloc(length*sizeof(char));
		sprintf(nodeValue, "%d", i);
		graph->AddNode(graph, nodeValue);
	}

	for(i = 0; i < n-1; i++)
	{
		graph->AddUndirectedEdge(graph, graph->nodes[i], graph->nodes[i+1]);
	}

	return graph;
}

int numInArray(int num, int* array, int size)
{
    int i;
    
    if(array == NULL)
    {
        return 0;
    }

    for(i = 0; i < size; i++)
    {
        if(array[i] == num)
        {
            return 1;
        }
    }

    return 0;
}

Graph* CreateRandomDAGIter(int n)
{
    Graph* graph = GraphAllocate(DIRECTED);
    int i, j, length, edgeNum, connectsNum, connections[3];
    char* nodeValue;

    edgeNum = rand()%n;

    for(i = 0; i < n; i++)
	{
		length = (int) log10(i+1) + 2;
		nodeValue = malloc(length*sizeof(char));
		sprintf(nodeValue, "%d", i);
		graph->AddNode(graph, nodeValue);
	}

    for(i = 0; i < edgeNum; i++)
    {
        connectsNum = rand()%3+1;
        memset(connections, 0, 3);

        for(j = 0; j < connectsNum; j++)
        {
            connections[j] = rand()%n;
            while(connections[j] <=i && !numInArray(connections[j], connections, connectsNum))
            {
                connections[j] = rand()%n;
            }
            graph->AddDirectedEdge(graph, graph->nodes[i], graph->nodes[connections[j]]);
        }
    }

    return graph;
}

Graph* CreateRandomCompleteWeightedGraph(int n)
{
    Graph* graph = GraphAllocate(WEIGHTED);
    int i, j, num, length;
    char* nodeValue;

    for(i = 0; i < n; i++)
    {
        length = (int) log10(i+1) + 2;
		nodeValue = malloc(length*sizeof(char));
		sprintf(nodeValue, "%d", i);
		graph->AddNode(graph, nodeValue);
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n-1; j++)
        {
            num = rand()%n;
            graph->AddWeightedEdge(graph, graph->nodes[i], graph->nodes[j], num);
        }
    }

    return graph;
}

Graph* CreateWeightedLinkedList(int n)
{
    Graph* graph = GraphAllocate(WEIGHTED);
    int i, num, length;
    char* nodeValue;

    for(i = 0; i < n; i++)
    {
        length = (int) log10(i+1) + 2;
		nodeValue = malloc(length*sizeof(char));
		sprintf(nodeValue, "%d", i);
		graph->AddNode(graph, nodeValue);
    }

    for(i = 0; i < n-1; i++)
    {
        num = rand()%n;
        graph->AddWeightedEdge(graph, graph->nodes[i], graph->nodes[i+1], num);
    }

    return graph;
}

Vec2* GetNeighbors(Vec2 currentPosition, int n, int* size)
{
    int i, nSize, x, y;
    Vec2 possibleNeighbors[] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    Vec2* neighbors = malloc(2*sizeof(Vec2));
    
    nSize = 0;
    for(i = 0; i < 4; i++)
    {
        x = possibleNeighbors[i].x + currentPosition.x;
        y = possibleNeighbors[i].y + currentPosition.y;
        if( x < 0 || x >= n || y < 0 || y >= n)
        {
            continue;
        }

        nSize++;
        if(nSize > 2)
        {
            neighbors = realloc(neighbors, nSize*sizeof(Vec2));
        }

        neighbors[nSize-1].x = x;
        neighbors[nSize-1].y = y;
    }

    *size = nSize;
    return neighbors;
}

Graph* CreateRandomGridGraph(int n)
{
    Graph* graph = GraphAllocate(GRID);
    int i, j, k, num, length, chance;
    Vec2 position, neighborPos;
    Vec2* neighbors;
    char* nodeValue;
    Node* nodeA, *nodeB;
    GHashTable *nodesHash;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            length = (int) log10(i*n+j+1) + 2;
            nodeValue = malloc(length*sizeof(char));
            sprintf(nodeValue, "%d", i*n+j);
            position.x = i;
            position.y = j;

            graph->AddGridNode(graph, nodeValue, position);
        }
    }

    nodesHash = graph->GetAllNodes(graph);

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            
            position.x = i;
            position.y = j;
            nodeA = g_hash_table_lookup(nodesHash, (gpointer) GetVec2Key(position));
            neighbors = GetNeighbors(position, n, &length);
            for(k = 0; k < length; k++)
            {
                chance = rand()%2;
                if(chance)
                {
                    neighborPos = neighbors[k];
                    nodeB = g_hash_table_lookup(nodesHash, (gpointer) GetVec2Key(neighborPos));
                    graph->AddUndirectedEdge(graph, nodeA, nodeB);
                }
            }
        }
    }
}