#include <vector>
#include <time.h>

using namespace std;

class Ga{
	public:		
	
		int mutationRate;
		int tournamentSize;
		int populationSize;
		int startCityIndex;
		
		Ga(int, int, int, int);
		
		void SortVector(vector<vector<float> > &vecRef);
		vector<City> CreateRoute(vector<City> cityList);
		vector<City> CreateRoute(City startCity, int routeSize);
		vector<vector<City> > InitialPopulation(vector<City> cityList);
		vector<vector<float> > RankRoutes(vector<vector<City> > &population);
		int Selection(vector<vector<float> > &fitnessResults);
		int GetTournamentResult(vector<vector<float> > &fitnessResults, vector<int> &tournamentContestant);
		bool CityCheck(vector<City> &vec, City city);
		void CrossOver(vector<City> &parent1, vector<City> &parent2, vector<City> &childRef1, vector<City> &childRef2);
		void Mutate(vector<City> &route);
		void ChangeWithWorstTour(int worstIndex, vector<City> &route, vector<vector<City> > &population);	
		int Run(vector<vector<City> > &pop);
};
