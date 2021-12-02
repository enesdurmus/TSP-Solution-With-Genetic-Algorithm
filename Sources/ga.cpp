#include "..\Headers\ga.h"

Ga::Ga(int mutationRate, int tournamentSize, int populationSize, int startCityIndex){
	this->tournamentSize = tournamentSize;
	this->mutationRate = mutationRate;
	this->populationSize = populationSize;
	this->startCityIndex = startCityIndex;
}

// Implementing Selection Sort
void Ga::SortVector(vector<vector<float> > &vecRef){
	float tempIndex, tempFitRes, j;
	for(int i = 1; i < vecRef.size(); i++){
		j = i;
		tempFitRes = vecRef[i][1];
		tempIndex = vecRef[i][0];

		while(j > 0 && tempFitRes < vecRef[j - 1][1]){
			vecRef[j][1] = vecRef[j - 1][1];
			vecRef[j][0] = vecRef[j - 1][0];
			j--;
		}
		
		vecRef[j][1] = tempFitRes;
		vecRef[j][0] = tempIndex;
	}
}

// To Create route with starting an ending city are same.
vector<City> Ga::CreateRoute(vector<City> cityList){
	vector<City> route;
	int listSize = cityList.size() - 1;
	
	// Adding start city.
	route.push_back(cityList.at(this->startCityIndex));
    cityList.erase(cityList.begin() + this->startCityIndex);
	    
    for(int i = 0; i < listSize; i++){
    	int index = rand() % cityList.size();
    	route.push_back(cityList.at(index));
    	cityList.erase(cityList.begin() + index);
	}
		
	// Adding end city same as start.
	route.push_back(route.at(0));
		
	return route;
}

// To create empty route.
vector<City> Ga::CreateRoute(City startCity, int routeSize){
	vector<City> route;
	City city; // Empty city
		
	route.push_back(startCity); // start city
	    
    for(int i = 1; i < routeSize - 1; i++){
    	route.push_back(city);
	}
	
	route.push_back(startCity); // end city

	return route;
}

vector<vector<City> > Ga::InitialPopulation(vector<City> cityList){
	vector<vector<City> > population;
	srand( (unsigned)time(0) );

	for(int i = 0; i < populationSize; i++){
		population.push_back(CreateRoute(cityList));
	}	
	
	return population;
}

vector<vector<float> > Ga::RankRoutes(vector<vector<City> > &population){
	vector<vector<float> > fitnessResults;
	
	for(int i = 0; i < population.size(); i++){
		vector<float> result;
		result.push_back((float) i);
		result.push_back(Fitness(population.at(i)).RouteFitness());
		fitnessResults.push_back(result);
	}
	
	SortVector(fitnessResults);
	return fitnessResults;
}

//Tournement Selection.
int Ga::Selection(vector<vector<float> > &fitnessResults){
	vector<int> tournamentContestant;		
	
	for(int j = 0; j < tournamentSize; j++){
		int index = rand() % fitnessResults.size();	
		tournamentContestant.push_back(fitnessResults[index][0]);
	}
			
	return GetTournamentResult(fitnessResults, tournamentContestant);
}

int Ga::GetTournamentResult(vector<vector<float> > &fitnessResults, vector<int> &tournamentContestant){
	int bestRankIndex = 0;
	int bestFitness = 0;
	
	for(int i = 0; i < tournamentContestant.size(); i++){
		if(fitnessResults[tournamentContestant.at(i)][1] > bestFitness){
			bestFitness = fitnessResults[tournamentContestant.at(i)][1];
			bestRankIndex = tournamentContestant.at(i);
		}
	}
	
	return bestRankIndex;
}

bool Ga::CityCheck(vector<City> &vec, City city){
	for(int i = 0; i < vec.size(); i++){
		if(vec[i].id == city.id){
			return true;
		}
	}
	return false;
}

// Modified Uniform Crossover 
void Ga::CrossOver(vector<City> &parent1, vector<City> &parent2, vector<City> &child1, vector<City> &child2){
	child1 = CreateRoute(parent1.at(0), parent1.size());
	child2 = CreateRoute(parent1.at(0), parent1.size());

	for(int i = 1; i < parent1.size() - 1; i++){
		if(rand() % 2 == 1){
			child1[i] = parent1[i];
			child2[i] = parent2[i];
		}
	}
		
	for(int i = 1; i < parent1.size() - 1; i++){
		
		if(child1[i].id == -1){
			for(int j = 0; j < parent2.size(); j++){
				if(!CityCheck(child1, parent2[j])){
					child1[i] = parent2[j];
					break;
				}
			}	
		}
		
		if(child2[i].id == -1){
			for(int j = 0; j < parent2.size(); j++){
				if(!CityCheck(child2, parent1[j])){
					child2[i] = parent1[j];
					break;
				}
			}
		}
	}
}

//Swap mutation
void Ga::Mutate(vector<City> &route){
	for(int i = 1; i < route.size() - 1; i++){
		if(rand() % 100 < mutationRate){
			int j = (rand() % (route.size() - 2)) + 1;
			swap(route[i], route[j]);
		}
	}
}

void Ga::ChangeWithWorstTour(int worstIndex, vector<City> &route, vector<vector<City> > &population){
	population[worstIndex] = route;
}

int Ga::Run(vector<vector<City> > &pop){
	vector<vector<float> > rankRoutes = RankRoutes(pop);	
	int parent1 = Selection(rankRoutes);
	int parent2 = Selection(rankRoutes);
	vector<City> child1, child2;
	CrossOver(pop.at(parent1), pop.at(parent2), child1, child2);
	Mutate(child1);
	Mutate(child2);
	ChangeWithWorstTour(rankRoutes[0][0], child1, pop);
	ChangeWithWorstTour(rankRoutes[1][0], child2, pop);

	cout << "best distance = " << Fitness(pop[rankRoutes[rankRoutes.size() - 1][0]]).RouteDistance() << endl;
	
	return rankRoutes[rankRoutes.size() - 1][0]; // best route index.
}
