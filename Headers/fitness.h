#include <vector>

class Fitness{
	public:
		Fitness(std::vector<City>);
		
		std::vector<City> route;
		int routeSize;
		float distance;
		float fitness;
		
		float RouteDistance();
		float RouteFitness();		
};
