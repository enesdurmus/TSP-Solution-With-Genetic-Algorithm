#include "..\Headers\fitness.h"
#include <iostream>
#include "math.h"
#include <stdlib.h>

Fitness::Fitness(std::vector<City> route){
	this->route = route;
	this->fitness = 0;
	this->distance = 0;
}

float Fitness::RouteDistance(){
	if(this->distance == 0){
		float disBetweenCities = 0;
		
		for(int i = 0; i < this->route.size(); i++){
			City fromCity = route.at(i);
			City toCity;
			if(i + 1 < this->route.size()){
				toCity = route.at(i + 1);
			}else{
				toCity = route.at(0);
			}
			disBetweenCities += fromCity.Distance(toCity);
		}
		
		this->distance = disBetweenCities;
	}
	
	return this->distance;
}

float Fitness::RouteFitness(){
	if(this->fitness == 0){
		this->fitness = 1 / (float) RouteDistance();
	}
	
	return this->fitness;
}
