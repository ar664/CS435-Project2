#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "node.h"

Node* NodeAllocate(char* val, Vec2 position)
{
    Node* node = malloc(sizeof(Node));

    node->data = val;
    node->weights = NULL;
    node->neighbors = NULL;
    node->neighborCount = 0;
    node->visited = 0;
    node->position = position;

    return node;
}

int NodeConnectedUndirected(Node* first, Node* second)
{
    int i;
    for(i = 0; i < first->neighborCount; i++)
    {
        if(first->neighbors[i] == second)
        {
            return 1;
        }
    }
    
    return 0;
}

void NodeAddNeighbor(Node* node, Node* neighbor)
{
    if(node == NULL || neighbor == NULL)
    {
        printf("NodeAddNeighbor: Attempted to add neighbor %p to node %p.\n", neighbor, node);
        return;
    }

    node->neighbors = realloc(node->neighbors, (node->neighborCount+1)*sizeof(Node*));
    node->neighbors[node->neighborCount] = neighbor;
    node->neighborCount++;
}

void NodeRemoveNeighbor(Node* node, Node* neighbor)
{
    Node** newNeighbors = malloc(node->neighborCount*sizeof(Node*));
    int i, j;

    if(node == NULL || neighbor == NULL)
    {
        printf("NodeRemoveNeighbor: Attempted to add neighbor %p to node %p.\n", neighbor, node);
        return;
    }

    j = 0;
    for(i = 0; i < node->neighborCount; i++)
    {
        if(node->neighbors[i] == neighbor)
        {
            continue;
        }
        newNeighbors[j] = node->neighbors[i];
        j++;
    }

    free(node->neighbors);
    node->neighbors = newNeighbors;
}

void NodeAddWeightedNeighbor(Node* node, Node* neighbor, int weight)
{
    if(node == NULL || neighbor == NULL)
    {
        printf("NodeAddWeightedNeighbor: Attempted to add neighbor %p to node %p.\n", neighbor, node);
        return;
    }
    if(weight < 0)
    {
        printf("NodeAddWeightedNeighbor: WARNING, Added Negative Weight\n");
    }

    node->neighbors = realloc(node->neighbors, (node->neighborCount+1)*sizeof(Node*));
    node->weights = realloc(node->weights, (node->neighborCount+1)*sizeof(int));
    node->neighbors[node->neighborCount] = neighbor;
    node->weights[node->neighborCount] = weight;
    node->neighborCount++;
}

void NodeRemoveWeightedNeighbor(Node* node, Node* neighbor)
{
    Node** newNeighbors = malloc(node->neighborCount*sizeof(Node*));
    int* newWeights = malloc(node->neighborCount*sizeof(int));
    int i, j;

    if(node == NULL || neighbor == NULL)
    {
        printf("NodeRemoveWeightedNeighbor: Attempted to add neighbor %p to node %p.\n", neighbor, node);
        return;
    }

    j = 0;
    for(i = 0; i < node->neighborCount; i++)
    {
        if(node->neighbors[i] == neighbor)
        {
            continue;
        }
        newNeighbors[j] = node->neighbors[i];
        newWeights[j] = node->weights[i];
        j++;
    }


    free(node->weights);
    free(node->neighbors);
    node->weights = newWeights;
    node->neighbors = newNeighbors;
}

int NodeIsGridNeighbor(Vec2 first, Vec2 second)
{
    if( abs(first.x - second.x) <= 1 && abs(first.y - second.y) <= 1)
    {
        return 1;
    }

    return 0;
}

char* NodeListToStr(Node** list, int maxNodes)
{
	int base10, i, curLen;
	char* listStr;

	base10 = (int) log10(maxNodes) + 2;
	listStr = malloc((maxNodes*base10+1)+sizeof(char));
	curLen = 0;

	for(i = 0; i < maxNodes && list[i]; i++)
	{
		sprintf(listStr+(curLen), " %s", list[i]->data);
		curLen += strlen(list[i]->data)+1;
	}

	listStr[curLen+1] = '\0';

	return listStr;
}

void PrintNodeList(char* name, Node** list, int maxNodes)
{
    char* nodeStr;

    nodeStr = NodeListToStr(list, maxNodes);
    printf("%s:%s\n", name, nodeStr);
    free(nodeStr);
}

u_int64_t GetVec2Key(Vec2 v)
{
    u_int64_t key;

    key = (u_int64_t) v.x<<32;
    key += v.y;

    return key;
}