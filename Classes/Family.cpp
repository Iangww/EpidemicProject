#include "Family.hpp"

Family::Family(Disease &inputDisease) : Environment{inputDisease}
{
}

void Family::Update()
{
	//The probability of any given member becoming infected can be computed from the total number of infectious members
	double uninfectedProbability = 1;
	for (std::list<Person *>::iterator i = visitors.begin(); i != visitors.end(); ++i)
	{
		if ((*i)->isInfectious())
		{
			uninfectedProbability *= 1 - disease.getInfectionChance();
		}
	}
	//Every person visits during every update, since family interactions cannot be avoided
	for (std::list<Person *>::iterator i = visitors.begin(); i != visitors.end(); ++i)
	{
		(*i)->infectChance(1 - uninfectedProbability);
	}
}

Environment *Family::Duplicate()
{
	//This function is used to create many identical copies of the prototype family when populating the city environment list
	Environment *output = new Family(disease);
	return output;
}
