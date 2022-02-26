#include "ACO.h"
#include "Ant.h"
#include <vector>
#include <random>
#include <iostream>
#include <ctime>
using namespace std;

vector<vector<int>> ACO::matrix;
vector<vector<float>> ACO::pheromones;
vector<Ant*> ACO::ants;
vector<int> ACO::bestPath;
vector<int> ACO::tabu;
float ACO::alpha;
float ACO::betha;
int ACO::size;
int ACO::numberOfIterations;
int ACO::bestGlobal;
float ACO::evaporation;
float ACO::das;
ACO::Algo ACO::type;

ACO::ACO(){}

ACO::~ACO(){}

int ACO::findSolution(Graph* graph, Params* params)
{
    // zmienne
    matrix = graph->getVector();
    size = graph->getSize();
    bestGlobal = INT_MAX;
    bestPath = vector<int>(size, 0);
    tabu = vector<int>();
    pheromones = vector<vector<float>>(size, vector<float>(size, (float)size / estimateCost()));
    int mCount = params->numberOfIterations * 0.1f;

    // parametry
    numberOfIterations = params->numberOfIterations;                                          // ilość iteracji programu
    int numberOfAnts = params->numberOfAnts;                                                  // ilość mrówek w każdym z etapów
    evaporation = params->evaporation;                                                        // współczynnik parowania feromonu
    alpha = params->alpha;                                                                    // współczynnik wpływu feromonu na wybór ścieżki
    betha = params->betha;                                                                    // współczynnik wpływu stopnia widoczności miasta
    type = (Algo)params->type;                                                                // typ używanego algorytmu
    das = 0.001f;                                                                             // ilość feromonu dla wariantu DAS

    while (numberOfIterations > 0)
    {
        // dodanie nowych mrówek
        for (int j = 0; j < numberOfAnts; j++)
            ants.push_back(new Ant(size, rand() % (size)+0));

        // przejście trasy przez mrówki
        for (Ant* ant : ants)
        {
            for (int i = 0; i < size - 1; i++)
                ant->addVertex(calcBestVertex(ant->getRoad()));
            
            // dodanie krawędzi powrotnej
            pair<int, int> temp = ant->getEnds();
            ant->addToCost(matrix[temp.second][temp.first]);
        }
        
        // ustawienie wartości feromonu oraz sprawdzenie czy znaleziono minimum
        refreshPheromones();

        ants.clear();
        tabu.clear();
        numberOfIterations--;
        if (numberOfIterations % mCount == 0)
            cout << "#";
    }
    cout << endl;
    //showPath();
    for (auto v : pheromones)
        v.clear();
    for (auto v : matrix)
        v.clear();
    ants.clear();
    matrix.clear();
    pheromones.clear();
    return bestGlobal;
}

void ACO::refreshPheromones()
{
    auto minAnt = min_element(ants.begin(), ants.end(), [](Ant* a, Ant* b) { return a->getCost() < b->getCost(); });

    if (minAnt[0]->getCost() < bestGlobal)
    {
        bestGlobal = minAnt[0]->cost;
        bestPath = minAnt[0]->getRoad();
    }

    if(type == Algo::CAS)  updateCAS();

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (pheromones[i][j] > 0.0001f)
                pheromones[i][j] *= evaporation;

}

pair<int,int> ACO::calcBestVertex(vector<int> antTabu)
{   
    int start = antTabu.back(), minIndex = -1;
    float maxValue = 0.0f,  currentValue = 0.0f, sum = 0.0f;
    vector<pair<float, int>> probability = vector<pair<float, int>>(size, make_pair(0.0f, -1));

    for (int i = 0; i < size; i++)
    {
        if (i != start)
        {
            if (std::find(antTabu.begin(), antTabu.end(), i) == antTabu.end())
            {
                probability[i].first = pow(pheromones[start][i], alpha) * pow(1.0f / matrix[start][i], betha);
                probability[i].second = i;
                sum += probability[i].first;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {   
        double calc = probability[i].first / sum;

        if (probability[i].first > 0.0f)
        {
            if (minIndex == -1)
            {
                maxValue = calc;
                minIndex = i;
            }

            if (calc > maxValue)
            {
                maxValue = calc;
                minIndex = i;
            }
        }
    }

    maxValue = matrix[start][minIndex];

    if(type == Algo::DAS)
        pheromones[start][minIndex] += das;
    else if(type == Algo::QAS)
        pheromones[start][minIndex] += 1.0f/maxValue;

    return make_pair(minIndex, maxValue);
}

bool ACO::sort_by_sec(const pair<float, int> &a, const pair<float, int> &b)
{
    return (a.first < b.first);
}

void ACO::updateCAS()
{
    vector<int> road;
    for (auto ant : ants)
    {
        int cost = ant->getCost();
        road = ant->getRoad();
        for (int i = 0; i < size - 1; i++)
        {
            if (i != size - 1)
                pheromones[road[i]][road[i + 1]] += 1.0f / cost;
            else
                pheromones[road[i]][road[0]] += 1.0f / cost;
        }
    }
}

void ACO::showPath()
{
    cout << "Najlepsza droga = ";
    for (auto vertex : bestPath)
    {
        cout << vertex << " -> ";
    }
    cout << bestPath[0] << endl;
}

int ACO::estimateCost()
{
    int cnn = 0;
    int before = rand() % (size)+0;
    tabu.push_back(before);
    int temp = 0;
    int minVal = INT_MAX;
    int minIndex = INT_MAX;

    for (int j = 0; j < size-1; j++)
    {
        int minVal = INT_MAX;
        for (int i = 0; i < size; i++)
        {
            if (find(tabu.begin(), tabu.end(), i) == tabu.end())
            {
                if (matrix[before][i] < minVal)
                {
                    minVal = matrix[before][i];
                    minIndex = i;
                }
            }
        }
        tabu.push_back(minIndex);
        cnn += minVal;
    }
    cnn += matrix[size-1][0];
    tabu.clear();
    return cnn;
}

int ACO::getNextVertex()
{   
    int value;
    do{value = rand() % (size)+0; } while (find(tabu.begin(), tabu.end(), value) != tabu.end());
    tabu.push_back(value);
    return value;
}
