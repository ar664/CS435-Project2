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
	Node** bfsRecList, **bfsIterList, **dfsRecList, **dfsIterList, **kahnsList, **mDFSList, **astarList;
	GHashTable* djikstrasCompleteSet, *djikstrasLinkedSet, *gridHash;
	Vec2 startPosition, endPosition;
	int nodeNum, startNode, endNode, i, listSize;
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

	listSize = 0;
	gridHash = randomGridGraph->GetAllNodes(randomGridGraph);
	startPosition.x = 0; startPosition.y = 0;
	endPosition.x = 99; endPosition.y = 99;

	astarList = astar( g_hash_table_lookup(gridHash, GetVec2Key(startPosition)) , g_hash_table_lookup(gridHash, GetVec2Key(endPosition)), &listSize);

	if(astarList == NULL)
	{
		printf("astar could not find path from (0,0) to (99,99).\n");
	}
	else
	{
		PrintGridNodeList("astarList", astarList, listSize);
	}
	
	return 0;
}