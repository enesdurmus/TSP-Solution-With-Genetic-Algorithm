#include "..\Headers\city.h"
#include <iostream>
#include "math.h"

City::City(){
	this->x = 0;
    this->y = 0;
    this->id = -1;
}

City::City(int x, int y, int id){
    this->x = x;
    this->y = y;
    this->id = id;
}

float City::Distance(City city){
    int disX = this->x - city.x;
    int disY = this->y - city.y;
    return sqrt(pow(disX, 2) + pow(disY, 2));
}


