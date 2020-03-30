#ifndef __PATHFINDING_H
#define __PATHFINDING_H

#include "graph.h"

Node** DFSRec(Node* start, Node* end);

Node** DFSIter(Node* start, Node* end);

Node** BFTRec(Graph* graph);

Node** BFTIter(Graph* graph);

Node** BFTRecLinkedList(Graph* graph);

Node** BFTIterLinkedList(Graph* graph);

#endif