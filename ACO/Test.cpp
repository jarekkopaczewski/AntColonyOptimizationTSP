#include "Test.h"
#include <windows.h>
#include <iostream>
#include "ACO.h"
#include "DataReader.h"
#include "Graph.h"
#include <iomanip>
#include <fstream>
using namespace std;

void Test::runTest()
{
    Graph* graph = new Graph();
    long long int frequency, start = 0, elapsed, sum, size = 0;
    int result = INT_MAX;
    int nmbrOfTests = 1;
    string path = "";
    int currentMin = INT_MAX;
    int currentMax = 0;
    int sumOfTest = 0;
    ACO aco = ACO();
    pair<int[2], string>* initValues = DataReader::readInitData();

    if (initValues == nullptr)
    {
        cout << "Program konczy prace." << endl;
        return;
    }

    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

    int numberOfFiles = initValues[0].first[0];
    string outputName = initValues[0].second + ".csv";
    ofstream outputFile;
    outputFile.open(outputName);
    outputFile << "Nazwa pliku,czas[s],czas[ms],ilosc testow,Blad, min, sredni, max, poprawny\n";

    for (int k = 1; k < numberOfFiles; k++)
    {
        sum = 0; path = ""; graph = DataReader::readFile((initValues[k].second));
        size = graph->getSize();

        cout << endl << "================ " << initValues[k].second << " ================ " << endl;
        cout << "================ Liczba testow " << initValues[k].first[0] << " ================ " << endl << endl;
        //graph->showMatrix();
        result = INT_MAX;
        int currentMax = 0;
        int sumOfTest = 0;

        /*cout << "T0 = " << size * 30 << endl;
        cout << "Chlodzenie = 0.9999" << endl;
        cout << "Dlugosc ery = 50" << endl;
        cout << "T koncowa =  0.01" << endl;*/

        for (int i = 0; i < initValues[k].first[0]; i++)
        {
            start = read_QPC();
            currentMin = aco.ACO::findSolution(graph);
            elapsed = read_QPC() - start;
            sum += elapsed;
            if (currentMin < result)
                result = currentMin;
            if (currentMin > currentMax)
                currentMax = currentMin;
            sumOfTest += currentMin;
        }

        printResult(size,sum, initValues[k].first[0], path, initValues[k].first[1], frequency);
        cout << "Blad: " << ((double)(result - initValues[k].first[1]) * 100.0 / initValues[k].first[1]) << "%" << endl;

        cout << "Sredni wynik = " << sumOfTest / initValues[k].first[0] << endl;
        cout << "Najlepszy wynik = " << result << endl;
        cout << "Najgorszy wynik = " << currentMax << endl;
        outputFile << initValues[k].second << "," << float(sum) / (initValues[k].first[0]) / frequency << "," << setprecision(3) << float(sum * 1000.0) / (initValues[k].first[0]) / frequency << "," << initValues[k].first[0] << ", " 
                   << ((double)(result - initValues[k].first[1]) * 100.0 / initValues[k].first[1]) << ", " << result << ", " << sumOfTest / initValues[k].first[0] << ", " << currentMax << ", " << initValues[k].first[1] << "\n";
    }
    outputFile.close();
    cout << "Wyniki zapisano do: " << outputName << endl << endl;
}

long long int Test::read_QPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

void Test::printResult(int size, long long int sum, int test, string& path, int result, long long int f)
{
    cout << "Optymalna droga ma dlugosc: " << result << endl;// << "Optymalna droga: ";
    //cout << path << endl;

    cout << "Sredni czas operacji[s] = " << setprecision(3) 
         << float(sum / float(test))/f << endl;

    cout << "Sredni czas operacji[ms] = " << setprecision(3) 
         << float(sum * 1000.0)/ float(test)/f << endl;

    cout << "Sredni czas operacji [us] = " << setprecision(3) 
         << float(sum * 1000000.0) / float(test)/f << endl << endl;
}
