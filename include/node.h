#ifndef __NODE_H
#define __NODE_H

typedef struct _Node Node;

struct _Node
{
    char*       data;
    Node**      neighbors;
    int         neighborCount;
};

Node* NodeAllocate(char* val);

void NodeAddNeighbor(Node* node, Node* neighbor);

void NodeRemoveNeighbor(Node* node, Node* neighbor);

#endif