#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <glib.h>
#include "graph.h"

Graph* CreateRandomUnweightedGraphIter(int n)
{
	Graph* graph = GraphAllocate();
	Node* nodeA, *nodeB;
	int i, length, edgeNum, randVal;
	char *nodeValue;
	
	edgeNum = rand()%n;

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

int main(int argc, char** argv)
{
	Graph* randomGraph, *linkedGraph;
	int nodeNum;

	nodeNum = 100;
	srand(time(0));

	randomGraph = CreateRandomUnweightedGraphIter(nodeNum);
	linkedGraph = CreateLinkedList(nodeNum);

	return 0;
}