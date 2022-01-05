#pragma once
#include "Graph.h"
#include <vector>
using namespace std;

class ACO
{
public:
	ACO();
	~ACO();
	static vector<vector<int>> matrix;
	static vector<vector<int>> feromon;
	static int size;
	static int findSolution(Graph* graph);
};

