#pragma once
#include <vector>

class Ant
{
public:
	Ant();
	Ant(int size, int start);
	~Ant();
	bool addVertex(int cost, int value);
	int getCost();
private:
	std::vector<int> road;
	int cost;
};

