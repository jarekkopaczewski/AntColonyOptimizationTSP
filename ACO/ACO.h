#pragma once
#include "Graph.h"
#include "Ant.h"
#include <vector>
#include "Params.h"
using namespace std;

class ACO
{
public:

	// construct 
	ACO();
	~ACO();

	// fun
	static int findSolution(Graph* graph, Params* params);
	static void refreshPheromones();
	static pair<int, int> calcBestVertex(vector<int> tabu);
	static void updateCAS();
	static void showPath();
	static int estimateCost();
	static int getNextVertex();
	static bool sort_by_sec(const pair<float, int>& a, const pair<float, int>& b);

	// static param
	static vector<vector<int>> matrix;
	static vector<vector<float>> pheromones;
	static vector<int> bestPath;
	static vector<int> tabu;
	static vector<Ant*> ants;
	static int size;
	static int numberOfIterations;
	static int bestGlobal;
	static float das;
	static float evaporation;
	static float alpha;
	static float betha;

	// enum
	enum class Algo {DAS = 0, QAS = 1, CAS = 2};
	static Algo type;
};

