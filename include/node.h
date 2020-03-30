#ifndef __NODE_H
#define __NODE_H

typedef struct _Node Node;

struct _Node
{
    char*       data;
    Node**      neighbors;
    int         neighborCount;
    int         visited;
};

Node* NodeAllocate(char* val);

int NodeConnectedUndirected(Node* first, Node* second);

void NodeAddNeighbor(Node* node, Node* neighbor);

void NodeRemoveNeighbor(Node* node, Node* neighbor);

#endif