#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <glib.h>
#include "graph.h"
#include "pathfinding.h"

GHashTable* dijkstras(Node* start)
{
	return NULL;
}

GHashTable* astart(Node* start)
{
	return NULL;
}

int main(int argc, char** argv)
{
	Graph* randomGraph, *linkedGraph, *randomDAG, *randomCompleteWeightGraph, *randomWeightLinkedGraph, *randomGridGraph;
	Node** bfsRecList, **bfsIterList, **dfsRecList, **dfsIterList;
	int nodeNum, startNode, endNode, noOp, i;
	char* strList;

	nodeNum = 1000;
	srand(time(0));

	//Project Part 1-3
	randomGraph = CreateRandomUnweightedGraphIter(nodeNum);
	linkedGraph = CreateLinkedList(nodeNum);

	bfsRecList = BFTRec(randomGraph);
	bfsIterList = BFTIter(randomGraph);

	strList = NodeListToStr(bfsRecList, nodeNum);
	printf("bfsRecList:%s\n", strList);
	free(strList);

	strList = NodeListToStr(bfsIterList, nodeNum);
	printf("bfsIterList:%s\n", strList);
	free(strList);

	dfsRecList = NULL;
	dfsIterList = NULL;
	
	//Randomly pick a start and end until a path is found.
	while(!dfsRecList)
	{
		startNode = rand()%nodeNum;
		endNode = rand()%nodeNum;

		while(startNode == endNode)
		{
			startNode = rand()%nodeNum;
			endNode = rand()%nodeNum;
		}

		printf("Starting at node %d , ending at node %d.\n", startNode, endNode);

		dfsIterList = DFSIter(randomGraph->nodes[startNode], randomGraph->nodes[endNode]);
		GraphClearVisits(randomGraph);
		dfsRecList = DFSRec(randomGraph->nodes[startNode], randomGraph->nodes[endNode]);
		GraphClearVisits(randomGraph);
	}
	
	strList = NodeListToStr(dfsRecList, nodeNum);
	printf("dfsRecList:%s\n", strList);
	free(strList);

	strList = NodeListToStr(dfsIterList, nodeNum);
	printf("dfsIterList:%s\n", strList);
	free(strList);

	//Project Part 4-7

	randomDAG = CreateRandomDAGIter(nodeNum);
	randomCompleteWeightGraph = CreateRandomCompleteWeightedGraph(nodeNum);
	randomWeightLinkedGraph = CreateWeightedLinkedList(nodeNum);
	randomGridGraph = CreateRandomGridGraph(100);

	return 0;
}