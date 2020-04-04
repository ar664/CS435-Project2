#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <glib.h>
#include "graph.h"
#include "pathfinding.h"

Graph* CreateRandomUnweightedGraphIter(int n)
{
	Graph* graph = GraphAllocate();
	Node* nodeA, *nodeB;
	int i, length, edgeNum, randVal;
	char *nodeValue;
	
	edgeNum = n + rand()%n;

	for(i = 0; i < n; i++)
	{
		length = (int) log10(i+1) + 2;
		nodeValue = malloc(length*(sizeof(char)));
		sprintf(nodeValue, "%d", i);
		graph->AddNode(graph, nodeValue);
	}

	for(i = 0; i < edgeNum; i++)
	{
		randVal = rand()%n;
		nodeA = graph->nodes[randVal];
		randVal = rand()%n;
		while(graph->nodes[randVal] != nodeA && NodeConnectedUndirected( nodeA, graph->nodes[randVal]) )
		{
			randVal = rand()%n;
		}
		nodeB = graph->nodes[randVal];
		graph->AddUndirectedEdge(graph, nodeA, nodeB);
	}

	return graph;
}

Graph* CreateLinkedList(int n)
{
	Graph* graph = GraphAllocate();
	int i, length;
	char* nodeValue;

	for(i = 0; i < n; i++)
	{
		length = (int) log10(i+1) + 2;
		nodeValue = malloc(length*sizeof(char));
		sprintf(nodeValue, "%d", i);
		graph->AddNode(graph, nodeValue);
	}

	for(i = 0; i < n-1; i++)
	{
		graph->AddUndirectedEdge(graph, graph->nodes[i], graph->nodes[i+1]);
	}

	return graph;
}

char* NodeListToStr(Node** list, int maxNodes)
{
	int base10, i, curLen;
	char* listStr;

	base10 = (int) log10(maxNodes) + 2;
	listStr = malloc((maxNodes*base10+1)+sizeof(char));
	curLen = 0;

	for(i = 0; list[i]; i++)
	{
		sprintf(listStr+(curLen), " %s", list[i]->data);
		curLen += strlen(list[i]->data)+1;
	}

	listStr[curLen+1] = '\0';

	return listStr;
}

int main(int argc, char** argv)
{
	Graph* randomGraph, *linkedGraph;
	Node** bfsRecList, **bfsIterList, **dfsRecList, **dfsIterList;
	int nodeNum, startNode, endNode, noOp, i;
	char* strList;

	nodeNum = 10;
	srand(time(0));

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
	//Malloc check
	dfsIterList = malloc(sizeof(Node*));
	free(dfsIterList);
	
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

	return 0;
}