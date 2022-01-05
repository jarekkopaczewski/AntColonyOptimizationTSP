#include "ACO.h"
#include "Ant.h"
#include <vector>
#include <random>
#include <iostream>
using namespace std;

vector<vector<int>> ACO::matrix;
vector<vector<int>> ACO::feromon;
int ACO::size;

ACO::ACO(){}

ACO::~ACO(){}

int ACO::findSolution(Graph* graph)
{
    // random
    srand((unsigned)time(NULL));

    // parameters
    int numberOfAnts = 5;

    // varibles
    matrix = graph->getVector();
    size = graph->getSize();
    feromon = vector<vector<int>>(size, vector<int>(size, 0));
    vector<Ant*> ants = vector<Ant*>(numberOfAnts, new Ant(size, rand() % (size)+0));
    




    return 0;
}
