#include "Sources/city.cpp"
#include "Sources/fitness.cpp"
#include "Sources/ga.cpp"
#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

int const tournamentSize = 36;
int const mutationRate = 2;
int const populationSize = 40;
int const startCityIndex= 50;

vector<City> FileRead(){
	string textLine;
	ifstream MyReadFile("Cities Coordinates.tsp");
	
	string delimiter = " ";
	
	vector<City> cities;
	
	while (getline (MyReadFile, textLine)) {
		if(textLine.at(0) >= 48 && textLine.at(0) <= 57){
		    string idToken = textLine.substr(0, textLine.find(delimiter));
		    textLine.erase(0, textLine.find(delimiter) + delimiter.length());
		    string xToken = textLine.substr(0, textLine.find(delimiter));
		    textLine.erase(0, textLine.find(delimiter) + delimiter.length());
		    string yToken = textLine.substr(0, textLine.find(delimiter));
			cities.push_back(City(atoi(xToken.c_str()), atoi(yToken.c_str()), atoi(idToken.c_str())));
		}
	}
	
	MyReadFile.close();
	return cities;
}

void PrintRoute(vector<City> &bestRoute){
	for(int i = 0; i < bestRoute.size(); i++){
		cout << bestRoute[i].id << " - ";
	}
	
	cout << endl;
}

int main(){
	
	Ga ga(mutationRate, tournamentSize, populationSize, startCityIndex);
	vector<vector<City> > pop = ga.InitialPopulation(FileRead());
	
	int bestRoute = 0;
	
	for(int i = 0; i < 5000; i++){
		bestRoute = ga.Run(pop);
	}
	
	PrintRoute(pop[bestRoute]);

	cout << "Press any key to close." << endl;
	char c = getch();

    return 0;
}


