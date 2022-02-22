# Table of contents
* [General info](#general-info)
* [Built With](#built-with)
* [Timing](#timing)
* [Algorithm](#algorithm)
* [Results](#results) 
* [License](#license)

# About The Project

## General info

<p class="text-justify">
The method used to design a solution to the given problem is the ant colony algorithm, which consists in
simulating the behavior of real ants looking for food. Despite their blindness, ants are able to detect and
optimize the route to a nearby food source. They use the phenomenon of stigmergy, which is communication
through changes in the environment. During their initially random journey in search of food, they leave behind a trace in the
pheromone trail behind them, which based on its intensity can be perceived by the rest of the herd as a favourable
to travel or not. It all depends on how long the pheromone has been left behind and how many ants have travelled
the same route - after some time of searching for a route, this results in the ants taking the shortest route found.
    
</p>

## Built With

* [C++](https://isocpp.org/)
* [Visual Studio](https://visualstudio.microsoft.com/pl/)

## Timing

```cpp

// varibles
long long int frequency, start = 0, elapsed, sum, size = 0; 
QueryPerformanceFrequency((LARGE_INTEGER*)&frequency); 

// read clock function
long long int Test::read_QPC() 
{ 
	LARGE INTEGER count; 
	QueryPerformanceCounter(&count); 
	return((long long int)count.QuadPart); 
}

// testing for loop
for (int i = 0; i < initvalues[k].first[0]; i++) 
{
	start = read_QPC(); 
	currentMin = sim.SimAnnealing::findSolution(graph, initValues[0].first[1], 0); 
	elapsed = read_QPC() - start; 
}

// console out results
cout << "Sredni czas operacji[s] = " << setprecision(3; << float(sum / float(test))/f << endl; 
cout << "Sredni czas operacji[ms] = " << setprecision(3) << float(sum * 1000.0)/ float(test)/f << endl; 
cout << "Sredni czas operacji [us] = " << setprecision(3) << float(sum * 1000000.0) / float(test)/f << endl << endl; 

```

## Algorithm

```cpp
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
```
## Results 
### QAS vs CAS

<img src="https://github.com/jarekkopaczewski/AntColonyOptimizationTSP/blob/225bfb8b2e64cfe1b3678019f6d5a5fa4e1f396e/QAS_vs_CAS.png" width="700"/>

## License

Distributed under the MIT License.

<p align="right">(<a href="#top">back to top</a>)</p>
