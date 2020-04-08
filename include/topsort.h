#ifndef __TOPSORT_H
#define __TOPSORT_H

#include "graph.h"

Node** Kahns(Graph* graph);

Node** mDFS(Graph* graph);


#endif