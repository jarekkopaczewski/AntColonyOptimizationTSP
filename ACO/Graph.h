#pragma once
#include <vector>
using namespace std;

class Graph
{
	public:
		Graph();
		Graph(int);
		~Graph();
		void setMatrix(int**);				//ustawia macierz -> wykorzystywane przy wczytywaniu z pliku
		void showMatrix();					//wyswietlanie macierzy
		int** getGraphMatrix();				//zwraca macierz
		int getSize();						//zwraca wielkosc - iloœæ wierzcho³ków
		int getBasicCycle();
		vector<vector<int>> getVector();
	private:
		vector<vector<int>> vecMatrix;
		int** matrix;						//macierz s¹siedztwa
		int	edgeNumber;						//iloœæ krawêdzi
		int vertexNumber;					//iloœæ wirzcholkow
		void clearMatrix();					//usuwanie tablicy -> u¿ywane przez destruktor
		int* calcSpaces();					//oblicza odstepy potrzebne do rownego wyswietlenia macierzy
		int calcLength(int);				//oblicza dlugosc liczby
};