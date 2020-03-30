#include <glib.h>
#include "pathfinding.h"

Node** DFSRec(Node* start, Node* end)
{
    Node** list;
    int i;

    start = start;
    start->visited = 1;

    for(i = 0; i < start->neighborCount; i++)
    {
        if(start->neighbors[i] == end)
        {
            list = calloc(2, sizeof(Node*));
            list[0] = end;
            return list;
        }
        else if(!start->neighbors[i]->visited)
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
                    list = realloc(list, (i+1)*sizeof(Node*));
                    memmove(list+1, list, (i)*sizeof(Node*));
                    list[0] = start->neighbors[i];
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
    Node* current, **list;
    int i, neighborNum;

    return NULL;
}

void BFTRecHelper(Node** list, int* listLength, GQueue* queue)
{
    Node* node;
    int i;

    if(queue->length == 0)
    {
        return;
    }

    

    node = g_queue_pop_head(queue);
    node->visited = 1;
    list[*listLength] = node;
    *listLength++;

    for(i = 0; i < node->neighborCount; i++)
    {
        if(!node->neighbors[i]->visited)
        {
            g_queue_push_head(queue, node->neighbors[i]);
        }
    }

    BFTRecHelper(list, listLength, queue);
}

Node** BFTRec(Graph* graph)
{
    int i, listLength;
    Node** list;
    GQueue* queue;

    queue = g_queue_new();
    list = calloc(graph->nodeCount+1, sizeof(Node*));
    listLength = 1;

    for(i = 0; i < graph->nodeCount; i++)
    {
        if(!graph->nodes[i]->visited)
        {
            g_queue_push_head(queue, graph->nodes[i]);
            BFTRecHelper(list, &listLength, queue);
        }
    }

    return list;
}

Node** BFTIter(Graph* graph)
{
    Node** list;
    GQueue* queue;
    Node* temp;
    int i, j, listLength;

    list = calloc(graph->nodeCount+1, sizeof(Node*));
    listLength = 0;

    for(i = 0; i < graph->nodeCount; i++)
    {
        while(queue->length != 0)
        {
            temp = g_queue_pop_head(queue);
            temp->visited = 1;
            list[listLength] = temp;
            listLength++;

            for(j = 0; j < temp->neighborCount; j++)
            {
                if(!temp->neighbors[j]->visited)
                {
                    g_queue_push_head(queue, temp->neighbors[j]);
                }
            }
        }
        if(!graph->nodes[i]->visited)
        {
            g_queue_push_head(queue, graph->nodes[i]);
        }
    }

    return list;
}

Node** BFTRecLinkedList(Graph* graph)
{
    return NULL;
}

Node** BFTIterLinkedList(Graph* graph)
{
    return NULL;
}