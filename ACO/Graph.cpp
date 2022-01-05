#include "Graph.h"
#include "DataReader.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

Graph::Graph()
{
	edgeNumber = 0;
	vertexNumber = 0;
	matrix = nullptr;
}

Graph::Graph(int vertexNumber)																// konstruktor incializujący parametry
{
	this->vertexNumber = vertexNumber;
	this->edgeNumber = (vertexNumber * (vertexNumber - 1)) / 2;
	matrix = nullptr;
}

Graph::~Graph()
{
	clearMatrix();
}


vector<vector<int>> Graph::getVector()
{
	return vecMatrix;
}

void Graph::setMatrix(int** matrix)															// wczytanie tablicy do grafu
{
	if (vertexNumber != 0) clearMatrix();
	this->matrix = matrix;
	for (int i = 0; i < vertexNumber; i++)
	{
		this -> matrix[i] = matrix[i];
	}

	vector<vector<int>> temp(vertexNumber, vector<int>(vertexNumber, INT_MAX));
	vecMatrix = temp;
	for (int i = 0; i < vertexNumber; i++)
		for (int j = 0; j < vertexNumber; j++)
			vecMatrix[i][j] = matrix[i][j];
}

void Graph::showMatrix()																	// wyświetlanie macierzy
{
	cout << endl;
	cout << "\t\t\t\t\t    ";
	int* spaces = calcSpaces();

	for (int k = 0; k < vertexNumber; k++)
	{
		if( k <= 9)
			cout << k << "  ";
		else
			cout << k << " ";
		for (int z = 0; z < spaces[k]-1; z++)
			cout << " ";
	}
	cout << endl << endl;
	for (int i = 0; i < vertexNumber; i++)
	{
		cout << "\t\t\t\t\t";
		if( i <= 9)
			cout << i << "   ";
		else
			cout << i << "  ";
		for (int j = 0; j < vertexNumber; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			cout << matrix[i][j];
			if (j != vertexNumber - 1)
			{
				int val = spaces[j] + (spaces[j] - calcLength(matrix[i][j]));
				for (int z = 0; z < val; z++)
					cout << " ";
			}
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n\n";
}

int** Graph::getGraphMatrix()
{
	return matrix;
}

int Graph::getSize()
{
	return vertexNumber;
}

int Graph::getBasicCycle()
{
	int sum = 0;
	for (int i = 0; i < vertexNumber; i++)
	{
		if (i + 1 != vertexNumber)
			sum += vecMatrix[i][i + 1];
		else
			sum += vecMatrix[i][0];
	}
	return sum;
}

void Graph::clearMatrix()
{
	delete[] matrix;
}

int* Graph::calcSpaces()
{
	int currentLongest = 1;
	int* spaces = new int[vertexNumber];
	for(int i = 0; i < vertexNumber; i++)
	{
		currentLongest = 1;
		for (int j = 0; j < vertexNumber; j++)
		{
			int temp = calcLength(matrix[j][i]);
			if (temp > currentLongest)
			{
				currentLongest = temp;
			}
		}
		spaces[i] = currentLongest;
	}
	return spaces;
}

int Graph::calcLength(int value)
{
	int result = 0;
	if (value < 0) result++;
	while(value > 0)
	{
		value /= 10;
		result++;
	}
	return result;
}


