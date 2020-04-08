#include <stdio.h>
#include <stdlib.h>
#include "topsort.h"

Node** Kahns(Graph* graph)
{
    GQueue* queue;
    Node** sortedList, *currentNode;
    int* inDegree, i, j, currentSize;

    sortedList = malloc(graph->nodeCount*sizeof(Node*));
    inDegree = calloc(graph->nodeCount, sizeof(int));
    queue = g_queue_new();
    currentSize = 0;

    for(i = 0; i < graph->nodeCount; i++)
    {
        for(j = 0; j < graph->nodes[i]->neighborCount; j++)
        {
            inDegree[atoi(graph->nodes[i]->neighbors[j]->data)]++;
        }
    }

    for(i = 0; i < graph->nodeCount; i++)
    {
        if(inDegree[i] == 0)
        {
            g_queue_push_head(queue, graph->nodes[i]);
        }
    }

    while(queue->length != 0)
    {
        currentNode = g_queue_pop_tail(queue);
        sortedList[currentSize] = currentNode;
        currentSize++;

        for(i = 0; i < currentNode->neighborCount; i++)
        {
            if(--inDegree[atoi(currentNode->neighbors[i]->data)] == 0)
            {
                g_queue_push_head(queue, currentNode->neighbors[i]);
            }
        }
    }

    g_queue_free(queue);
    free(inDegree);

    return sortedList;
}

Node** mDFS(Graph* graph)
{
    GQueue* queue, *visited;
    Node** sortedList, *currentNode;
    int i, j;

    sortedList = malloc(graph->nodeCount*sizeof(Node*));
    queue = g_queue_new();
    visited = g_queue_new();

    for(i = 0; i < graph->nodeCount; i++)
    {
        if(!graph->nodes[i]->visited)
        {
            g_queue_push_head(queue, graph->nodes[i]);
        }

        while(queue->length != 0)
        {
            currentNode = g_queue_pop_head(queue);
            g_queue_push_head(visited, currentNode);
            currentNode->visited = 1;

            for(j = 0; j < currentNode->neighborCount; j++)
            {
                if(!currentNode->neighbors[j]->visited)
                {
                    g_queue_push_head(queue, currentNode->neighbors[j]);
                }
                
            }
        }
    }

    for(i = 0; i < graph->nodeCount; i++)
    {
        sortedList[i] = g_queue_pop_head(visited);
    }

    return sortedList;
}