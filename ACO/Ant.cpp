#include "Ant.h"
#include <vector>
using namespace std;

Ant::Ant(){}

Ant::Ant(int size, int start)
{
    this->road = vector<int>(size, INT_MAX);
    this->cost = 0;
    this->road.push_back(start);
}

Ant::~Ant()
{
}

bool Ant::addVertex(int index, int value)
{
    // je¿eli tablica zawieraj¹ca drogê nie posiada zadanego elementu to jest on do niej dodawany
    // aktualizowany jest równie¿ koszt drogi przebyty przez mrówkê
    if (std::find(road.begin(), road.end(), index) == road.end()) 
    {
        road.push_back(index);
        cost += value;
        return true;
    }
    return false;
}

int Ant::getCost()
{
    return this->cost;
}
