#include "Disease.hpp"

Disease::Disease(int inputIncubation, int inputRecovery, double inputDeath, double inputChance, double inputSymptoms) : incubationDays{inputIncubation}, recoveryDays{inputRecovery}, deathRate{inputDeath}, infectionChance{inputChance}, symptomaticChance{inputSymptoms}
{
	//Throw invalid input object if an input is not in the appropriate range
	if (incubationDays < 0 || recoveryDays < 0 || deathRate < 0 || deathRate > 1 || infectionChance < 0 || infectionChance > 1 || symptomaticChance < 0 || symptomaticChance > 1)
	{
		throw invalidInputs{};
	}
}

int Disease::getIncubationDays() const
{
	//Getter for incubationDays
	return incubationDays;
}

int Disease::getRecoveryDays() const
{
	//Getter for recoveryDays
	return recoveryDays;
}

double Disease::getDeathRate() const
{
	//Getter for deathRate
	return deathRate;
}

double Disease::getInfectionChance() const
{
	//Getter for infectionChance
	return infectionChance;
}

double Disease::getSymptomaticChance() const
{
	//Getter for symptomaticChance
	return symptomaticChance;
}