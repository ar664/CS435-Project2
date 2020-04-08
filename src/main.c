#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <glib.h>
#include "graph.h"
#include "pathfinding.h"
#include "topsort.h"

int main(int argc, char** argv)
{
	Graph* randomGraph, *linkedGraph, *randomDAG, *randomCompleteWeightGraph, *randomWeightLinkedGraph, *randomGridGraph;
	Node** bfsRecList, **bfsIterList, **dfsRecList, **dfsIterList, **kahnsList, **mDFSList;
	GHashTable* djikstrasCompleteSet, *djikstrasLinkedSet, *astartSet;
	int nodeNum, startNode, endNode, noOp, i;
	char* strList;

	nodeNum = 1000;
	srand(time(0));

	//Project Part 1-3
	randomGraph = CreateRandomUnweightedGraphIter(nodeNum);
	linkedGraph = CreateLinkedList(nodeNum);

	bfsRecList = BFTRec(randomGraph);
	bfsIterList = BFTIter(randomGraph);

	PrintNodeList("bfsRecList", bfsRecList, nodeNum);
	PrintNodeList("bfsIterList", bfsIterList, nodeNum);

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
	
	PrintNodeList("dfsRecList", dfsRecList, nodeNum);
	PrintNodeList("dfsIterList", dfsIterList, nodeNum);

	//Project Part 4-7

	randomDAG = CreateRandomDAGIter(nodeNum);
	randomCompleteWeightGraph = CreateRandomCompleteWeightedGraph(nodeNum);
	randomWeightLinkedGraph = CreateWeightedLinkedList(nodeNum);
	randomGridGraph = CreateRandomGridGraph(100);

	kahnsList = Kahns(randomDAG);
	mDFSList = mDFS(randomDAG);

	PrintNodeList("kahnsList", kahnsList, nodeNum);
	PrintNodeList("mDFSList", mDFSList, nodeNum);

	djikstrasCompleteSet = djikstras(randomCompleteWeightGraph->nodes[0]);
	djikstrasLinkedSet = djikstras(randomWeightLinkedGraph->nodes[0]);

	PrintHashTableKVPairs("djistrasCompleteSet", djikstrasCompleteSet);
	PrintHashTableKVPairs("djikstrasLinkedSet", djikstrasLinkedSet);


	return 0;
}