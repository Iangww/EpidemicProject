#include "PublicSpace.hpp"

PublicSpace::PublicSpace(Disease &inputDisease, double inputSick, double inputVulnerable, double inputDistance) : Environment{inputDisease}, distanceLevel{inputDistance}, stayHomeIfSick{inputSick}, stayHomeIfVulnerable{inputVulnerable} {}

void PublicSpace::Update()
{
	//The probability of any given member becoming infected can be computed from the total number of infectious visitors
	double uninfectedProbability = 1;
	for (std::list<Person *>::iterator i = visitors.begin(); i != visitors.end(); ++i)
	{
		if ((*i)->isInfectious())
		{
			//Probability of visiting is reduced if symptomatic
			if ((*i)->isSymptomatic())
			{
				uninfectedProbability *= 1 - distanceLevel * disease.getInfectionChance();
			}
			else
			{
				uninfectedProbability *= 1 - stayHomeIfSick * distanceLevel * disease.getInfectionChance();
			}
		}
	}
	for (std::list<Person *>::iterator i = visitors.begin(); i != visitors.end(); ++i)
	{
		//Probability of visiting is also reduced if highly vulnerable, where overallHealth < 0.3 is considered highly vulnerable
		if ((*i)->getHealth() <= 5)
		{
			(*i)->infectChance(stayHomeIfVulnerable * (1 - uninfectedProbability));
		}
		else
		{
			(*i)->infectChance(1 - uninfectedProbability);
		}
	}
}

Environment *PublicSpace::Duplicate()
{
	//This function is used to create many identical copies of the prototype publicSpace when populating the city environment list
	Environment *output = new PublicSpace(disease, stayHomeIfSick, stayHomeIfVulnerable, distanceLevel);
	return output;
}