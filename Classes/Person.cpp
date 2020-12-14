#include "Person.hpp"

Person::Person(int input_health, std::mt19937 &inputRandom, Disease &inputDisease) : disease{inputDisease}, overallHealth{input_health}, infectedDays{-1}, random{inputRandom}, alive{true}, symptomatic{false} {}

int Person::getInfectedDays() const
{
	//Getter for infectedDays
	return infectedDays;
}

bool Person::isInfectious() const
{
	//Returns positive if this person is alive and in the infectious stage of illness
	return (alive && infectedDays >= disease.getIncubationDays() && infectedDays < disease.getRecoveryDays());
}

bool Person::isSymptomatic() const
{
	//Returns positive if this person has observed symptoms of disease and is alive
	return (alive && symptomatic && infectedDays < disease.getRecoveryDays());
}

int Person::getHealth() const
{
	//Getter for overallHealth
	return overallHealth;
}

void Person::infectChance(double probability)
{
	//This function infects this person with a certain probability, that probability being given by the input double
	if (infectedDays == -1 && (double)random() / random.max() <= probability)
	{
		infectedDays = 0;
	}
}

void Person::improveCondition()
{
	//This function improves the health of a person to counteract the damage done by the disease. This function is used by the Hospital environment
	overallHealth++;
}

bool Person::updatePerson()
{
	//This function returns true if the person being updated died that day. If they are already dead, no updating is needed and we can immediately return false
	if (!alive)
	{
		return false;
	}
	if (infectedDays >= 0)
	{
		infectedDays++;
	}
	//If the incubation period is over but the person is not recovered, they lose overall health proportional to a random number and the disease's death rate, and have a probability of beginning to exhibit symptoms
	if (infectedDays >= disease.getIncubationDays() && infectedDays < disease.getRecoveryDays())
	{
		if ((double)random() / random.max() < disease.getDeathRate())
		{
			overallHealth--;
		}
		if ((double)random() / random.max() < disease.getSymptomaticChance())
		{
			symptomatic = true;
		}
	}
	//If overall health is below 0, the person dies and the function returns true
	if (overallHealth <= 0)
	{
		alive = false;
		return true;
	}
	//If not dead, return false after updating
	return false;
}