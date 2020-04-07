#ifndef __NODE_H
#define __NODE_H

#include <glib.h>

typedef struct _Vec2 Vec2;

struct _Vec2
{
    int         x:32;
    int         y:32;
};

u_int64_t GetVec2Key(Vec2 v);

typedef struct _Node Node;

struct _Node
{
    char*       data;
    Node**      neighbors;
    int*        weights;
    int         neighborCount;
    int         visited;
    Vec2        position;
};

Node* NodeAllocate(char* val, Vec2 position);

int NodeConnectedUndirected(Node* first, Node* second);

int NodeIsGridNeighbor(Vec2 first, Vec2 second);

void NodeAddNeighbor(Node* node, Node* neighbor);

void NodeRemoveNeighbor(Node* node, Node* neighbor);

void NodeAddWeightedNeighbor(Node* node, Node* neighbor, int weight);

void NodeRemoveWeightedNeighbor(Node* node, Node* neighbor);

char* NodeListToStr(Node** list, int maxNodes);

#endif