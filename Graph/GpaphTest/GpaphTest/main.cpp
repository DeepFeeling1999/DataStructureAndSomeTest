#include<iostream>
#include<cstdlib>
#include"Graph.h"
int main(void)
{
	int ar[5][5] = {
		{0,2,5,0,0},
		{0,0,2,6,1},
		{0,0,0,7,1},
		{0,0,2,0,4},
		{0,0,0,0,0},
	};
	int visit1[5] = { 0 };
	Graph graph;
	GreatGraph(&graph, ar);

	std::cout << "DFS : ";
	DFS(&graph, visit1, 1);

	int visit2[5] = { 0 };
	std::cout << "\nBFS : ";
	BFS(&graph, visit2,1);


	DestroyGraph(&graph);

	system("pause");
	return 0;
}