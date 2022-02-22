# Table of contents
* [General info](#general-info)
* [Built With](#built-with)
* [Timing](#timing)
* [Algorithm](#algorithm)
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
	while(temperature > absoluteTemperature)
	{
		int era = 0;
		tempMinPermutation = permutation;

		while(era < K)
		{
			tempPermutation = tempMinPermutation;
			if (type == 1)
				invert(tempPermutation);
			else if (type == 2)
				insert(tempPermutation);
			else
				swapp(tempPermutation);
			
			deltaDistance = getTourLength(tempPermutation);

			if ((deltaDistance < tempMin) ? 1 : exp(-(deltaDistance - tempMin) / temperature) > dis(e))
			{
				tempMin = deltaDistance;
				swap(tempMinPermutation, tempPermutation);
			}
			era++;
		}

		if ((tempMin < distance) ? 1 : exp(-(tempMin - distance) / temperature) > dis(e))
		{
			distance = tempMin;
			swap(tempMinPermutation, permutation);
		}

		temperature = coolingType == 1 ? temperature / (a + b * K) : temperature * coolingRate;
	}
	return distance ;
```
## Ini file

/number of tests ; result ; file name/

<img src="https://github.com/jarekkopaczewski/Simulated-Annealing-TSP/blob/39f29c3f45d6113c4c68bb2fcf75b1d27139e434/ini.png" width="330"/>

## Results 
### Greedy vs steepest

<img src="https://github.com/jarekkopaczewski/Simulated-Annealing-TSP/blob/b99f54ececcbb3fa15f81003e0d51eb24e74a593/greedy_vs_steepest.png" width="700"/>

### Choice of neighbor

<img src="https://github.com/jarekkopaczewski/Simulated-Annealing-TSP/blob/b99f54ececcbb3fa15f81003e0d51eb24e74a593/neighbor.png" width="700"/>

## License

Distributed under the MIT License.

<p align="right">(<a href="#top">back to top</a>)</p>
