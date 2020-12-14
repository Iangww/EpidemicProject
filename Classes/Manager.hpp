#include <fstream>
#include "City.hpp"

class Manager
{
public:
	Manager(std::string, std::string, std::string);
	void runExperiment();

private:
	int population;
	double averageFamily;
	double averageWorkplace;
	int hospitalBedsFiveK;
	int incubationDays;
	int recoveryDays;
	double deathRate;
	double infectionChance;
	double symptomaticChance;
	std::string planFile;
	std::string outputFile;
};
