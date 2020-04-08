#include <stdio.h>
#include <glib.h>
#include "pathfinding.h"

Node** DFSRec(Node* start, Node* end)
{
    Node** list;
    int i;

    start = start;
    start->visited = 1;

    if(start == NULL || end == NULL)
    {
        printf("DFSRec: Given start %p and end %p.\n", start, end);
        return NULL;
    }

    if(start == end)
    {
        list = (Node**) calloc(2, sizeof(Node*));
        list[0] = end;
        return list;
    }

    for(i = 0; i < start->neighborCount; i++)
    {  
        if(!start->neighbors[i]->visited)
        {
            list = DFSRec(start->neighbors[i], end);

            if(list == NULL)
            {
                continue;
            }

            for(i = 0; list[i]; i++)
            {
                if(list[i] == end)
                {
                    list = realloc(list, (i+3)*sizeof(Node*));
                    memmove(list+1, list, (i+2)*sizeof(Node*));
                    list[0] = start;
                    return list;
                }
            }
        }
    }

    return NULL;
}

Node** DFSIter(Node* start, Node* end)
{
    GQueue *stack;
    GHashTable *parent;
    Node* current, **list;
    int i, hasUnvisitedNeighbors, pathSize;

    if(start == NULL || end == NULL)
    {
        printf("DFSIter: Given start %p and end %p.\n", start, end);
        return NULL;
    } 

    parent = g_hash_table_new(g_direct_hash, g_direct_equal);
    stack = g_queue_new();
    g_hash_table_insert(parent, start, NULL);
    g_queue_push_head(stack, start);

    while(!g_queue_is_empty(stack))
    {
        current = g_queue_peek_head(stack);
        if(current == end)
        {
            break;
        }
        current->visited = 1;
        hasUnvisitedNeighbors = 0;
        for(i = 0; i < current->neighborCount; i++)
        {
            if(current->neighbors[i]->visited)
            {
                continue;
            }
            g_hash_table_insert(parent, current->neighbors[i], current);
            g_queue_push_head(stack, current->neighbors[i]);
            hasUnvisitedNeighbors = 1;
        }
        if(!hasUnvisitedNeighbors)
        {
            g_queue_pop_head(stack);
        }
    }

    if(current == end)
    {
        //Get size of path to allocate
        current = g_hash_table_lookup(parent, current);
        pathSize = 2;
        while(current != start)
        {
            current = g_hash_table_lookup(parent, current);
            pathSize++;
        }
        current = end;
        list = malloc((pathSize+1)*sizeof(Node*));
        list[pathSize] = NULL;

        for(i = pathSize-1; i >= 0; i--)
        {
            list[i] = current;
            current = g_hash_table_lookup(parent, current);
        }

        g_queue_free(stack);
        g_hash_table_destroy(parent);

        return list;
    }

    g_queue_free(stack);
    g_hash_table_destroy(parent);

    return NULL;
}

void BFTRecHelper(Node** list, int* listLength, Node* node)
{
    int i, neighborsVisited;

    neighborsVisited = 0;

    for(i = 0; i < node->neighborCount; i++)
    {
        if(!node->neighbors[i]->visited)
        {
            node->neighbors[i]->visited = 1;
            list[*listLength] = node->neighbors[i];
            *listLength = *listLength + 1;
            neighborsVisited = 1;
        }
    }

    if(neighborsVisited)
    {
        for(i = 0; i <  node->neighborCount; i++)
        {
            BFTRecHelper(list, listLength, node->neighbors[i]);
        }
    }
    
}

Node** BFTRec(Graph* graph)
{
    int i, listLength;
    Node** list;

    list = calloc(graph->nodeCount+1, sizeof(Node*));
    listLength = 0;

    for(i = 0; i < graph->nodeCount; i++)
    {
        if(!graph->nodes[i]->visited)
        {
            graph->nodes[i]->visited = 1;
            list[listLength] = graph->nodes[i];
            listLength++;
            BFTRecHelper(list, &listLength, graph->nodes[i]);
        }
    }

    GraphClearVisits(graph);

    return list;
}

Node** BFTIter(Graph* graph)
{
    Node** list;
    GQueue* queue;
    Node* temp;
    int i, j, listLength;

    queue = g_queue_new();
    list = calloc(graph->nodeCount+1, sizeof(Node*));
    listLength = 0;

    for(i = 0; i < graph->nodeCount; i++)
    {
        while(queue->length != 0)
        {
            temp = g_queue_pop_tail(queue);
            

            for(j = 0; j < temp->neighborCount; j++)
            {
                if(!temp->neighbors[j]->visited)
                {
                    g_queue_push_head(queue, temp->neighbors[j]);
                    temp->neighbors[j]->visited = 1;
                    list[listLength] = temp->neighbors[j];
                    listLength++;
                }
            }
        }
        if(!graph->nodes[i]->visited)
        {
            g_queue_push_head(queue, graph->nodes[i]);
            graph->nodes[i]->visited = 1;
            list[listLength] = graph->nodes[i];
            listLength++;
        }
    }

    g_queue_free(queue);
    GraphClearVisits(graph);

    return list;
}

Node** BFTRecLinkedList(Graph* graph)
{
    return BFTRec(graph);
}

Node** BFTIterLinkedList(Graph* graph)
{
    return BFTIter(graph);
}

GHashTable* djikstras(Node* start)
{
    GHashTable* shortestDistance, *parents, *availableNeighbors;
    GHashTableIter iter;
    Node* minNeighbor, *currentNeighbor;
    int i;
    u_int64_t minNeighborDistance, neighborValue, currentDistance, currentNeighborDistance;

    if(start == NULL)
    {
        printf("djikstras: Attempted to start on NULL node.\n");
        return NULL;
    }

    shortestDistance = g_hash_table_new(g_direct_hash, g_direct_equal);
    parents = g_hash_table_new(g_direct_hash, g_direct_equal);
    availableNeighbors = g_hash_table_new(g_direct_hash, g_direct_equal);

    g_hash_table_insert(shortestDistance, start, 0);
    for(i = 0; i < start->neighborCount; i++)
    {
        g_hash_table_insert(availableNeighbors, start->neighbors[i], (gpointer) (u_int64_t) start->weights[i]);
        g_hash_table_insert(parents, start->neighbors[i], start);
    }

    while(g_hash_table_size(availableNeighbors) != 0)
    {
        minNeighborDistance = INFINITE_INT;
        g_hash_table_iter_init(&iter, availableNeighbors);
        for(i = 0; i < g_hash_table_size(availableNeighbors); i++)
        {
            g_hash_table_iter_next(&iter, (gpointer) &currentNeighbor, (gpointer) &neighborValue);

            if(neighborValue < minNeighborDistance)
            {
                minNeighbor = currentNeighbor;
                minNeighborDistance = neighborValue;
            }
        }

        g_hash_table_insert(shortestDistance, minNeighbor, (gpointer) minNeighborDistance);
        g_hash_table_remove(availableNeighbors, minNeighbor);

        for(i = 0; i < minNeighbor->neighborCount; i++)
        {
            if(minNeighbor->neighbors[i] == g_hash_table_lookup(parents, minNeighbor))
            {
                continue;
            }

            currentDistance = (u_int64_t) g_hash_table_lookup(shortestDistance, minNeighbor->neighbors[i]);
            currentNeighborDistance = minNeighbor->weights[i] + minNeighborDistance;

            if(currentDistance == 0 || currentNeighborDistance  < currentDistance)
            {
                g_hash_table_insert(availableNeighbors, minNeighbor->neighbors[i], (gpointer) currentNeighborDistance);
                g_hash_table_insert(parents, minNeighbor->neighbors[i], minNeighbor);
            }
        }
    }

    g_hash_table_destroy(availableNeighbors);
    g_hash_table_destroy(parents);

    return shortestDistance;

}

GHashTable* astar(Node* start)
{

}

void PrintHashTableKVPairs(char* name, GHashTable* hashtable)
{
    int i;
    Node* key;
    u_int64_t value;
    GHashTableIter iter;

    if(hashtable == NULL)
    {
        printf("PrintHashTableKVPairs: Attempted to print NULL hashtable.\n");
        return;
    }

    printf("%s (UnOrdered)\n", name);

    g_hash_table_iter_init(&iter, hashtable);

    for(i = 0; i < g_hash_table_size(hashtable)-1; i++)
    {
        g_hash_table_iter_next(&iter, (gpointer) &key, (gpointer) &value);
        printf("%s: %ld, ", key->data, value);
    }
    
    g_hash_table_iter_next(&iter, (gpointer) &key, (gpointer) &value);
    printf("%s: %ld\n", key->data, value);
}