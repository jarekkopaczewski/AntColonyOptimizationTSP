#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "DataReader.h"
#include <conio.h>
using namespace std;

Graph* DataReader::readFile(string name)                                            // typ definiuje rodzaj grafu (nie)skierowany
{
    Graph* graph = new Graph();
    int size = 0;
    std::string fileName = "";

    if (name == "")
    {
        fileName = readName();
        fileName = fileName + ".txt";
    }
    else
    {
        fileName = name + ".txt";
    }

    fstream fileData;
    fileData.open(fileName, fstream::in);

    if (fileData.good())
    {
        fileData >> size;
        graph = new Graph(size);                                                      // tworzenie grafu o zadanych parametrach
        int** tab = new int*[size];

        for (int i = 0; i < size; i++)
        {
            tab[i] = new int[size];
            for (int j = 0; j < size; j++)
            {
                fileData >> tab[i][j];
            }
        }
        graph->setMatrix(tab);                                                        // ustawienie wczytanej macierzy w grafie
    }
    else
    {
        cout << "Blad pliku!" << endl;
        cout << "Plik nie zostal wczytany." << endl;
        cout << "\nWcisnij dowolny klawisz..." << endl;
        int znak = _getch();
    }
    fileData.close();
    return graph;
}

pair<int[2], string>* DataReader::readInitData()
{
    int size = 0;
    int test = 0, solution = 0;
    string name = "";
    pair<int[2], string>* init = nullptr;

    std::string fileName = readName();
    fileName = fileName + ".txt";

    fstream fileData;
    fileData.open(fileName, fstream::in);

    if (fileData.good())
    {
        fileData >> size >> solution >> name;
        init = new pair<int[2], string>[size];
        init[0].first[0] = size;
        init[0].first[1] = solution;
        init[0].second = name;

        for (int x = 1; x < size; x++)
        {
            fileData >> test >> solution >> name;
            init[x].first[0] = test;
            init[x].first[1] = solution;
            init[x].second = name;
            cout << init[x].first[0] << ", " << init[x].first[1] <<  ", " << init[x].second << endl;
        }
    }
    else
    {
        cout << "Blad pliku!" << endl;
        cout << "Plik nie zostal wczytany." << endl;
        cout << "\nWcisnij dowolny klawisz..." << endl;
        int znak = _getch();
        return nullptr;
    }
    fileData.close();
    return init;
}

string DataReader::readName()
{
    string temp;
    do
    {
        cout << "Nazwa pliku konfiguracyjnego(bez rozszerzenia): ";
        cin >> temp;
        if (sizeof(temp) == 0) cout << "Nazwa pliku nie moze byc pusta!" << endl;
    } while (sizeof(temp) == 0);
    return temp;
}
