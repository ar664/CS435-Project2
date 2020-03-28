#include <stdio.h>
#include <stdlib.h>
#include "node.h"

Node* NodeAllocate(char* val)
{
    Node* node = malloc(sizeof(Node));

    node->data = val;
    node->neighbors = NULL;
    node->neighborCount = 0;

    return node;
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
    Node** newneighbors = malloc(node->neighborCount*sizeof(Node*));
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
        newneighbors[j] = node->neighbors[i];
        j++;
    }

    free(node->neighbors);
    node->neighbors = newneighbors;
}