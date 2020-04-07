#ifndef __PATHFINDING_H
#define __PATHFINDING_H

#include "graph.h"

/**
 * @brief Recursively searches for end node from start node via DFS Algorithm
 * 
 * @param start     The node to start from
 * @param end       The node to end with
 * @return Node**   A NULL terminated list of nodes if path found, else NULL
 */
Node** DFSRec(Node* start, Node* end);

/**
 * @brief Iteratively searched for end node from start node via DFS Algorithm
 * @note Implements a hashtable for parent lookup & stack
 * 
 * @param start     The node to start from
 * @param end       The node to end with
 * @return Node**   A NULL terminated list of nodes if path found, else NULL
 */
Node** DFSIter(Node* start, Node* end);

/**
 * @brief Recursively traverses the graph via BFS Algorithm
 * 
 * @param graph The graph to traverse
 * @return Node**   A null terminated list of nodes that is the order of traversal
 */
Node** BFTRec(Graph* graph);

/**
 * @brief Iteratively traverses the graph via BFS Algorithm
 * 
 * @param graph The graph to traverse
 * @return Node**   A null terminated list of nodes that is the order of traversal
 */
Node** BFTIter(Graph* graph);

Node** BFTRecLinkedList(Graph* graph);
Node** BFTIterLinkedList(Graph* graph);

Node** Kahns(Graph* graph);

Node** mDFS(Graph* graph);

#endif