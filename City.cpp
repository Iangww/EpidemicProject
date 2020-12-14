#include "City.hpp"

City::City(Disease &inputDisease, int inputPopulation, double inputFamily, double inputWorkplace, int inputBeds, Plan &inputPlan) : disease{inputDisease}, plan{inputPlan}, population{inputPopulation}, averageFamily{inputFamily}, averageWorkplace{inputWorkplace}, hospitalBedsFiveK{inputBeds}
{
	std::random_device randomSeed;
	random.seed(randomSeed());
	int initialInfections = 10;
	for (int i = 0; i < population; i++)
	{
		people.emplace_back(new Person(3 + (i % 8), random, disease));
		if (i < initialInfections)
		{
			people.back().get()->infectChance(1);
		}
	}
	//Prototype objects for each environment are created using the parameters contained in the Plan object
	std::unique_ptr<Environment> baseFamily(new Family(disease));
	std::unique_ptr<Environment> baseWorkplace(new PublicSpace(disease, plan.workIfSick(), plan.workIfVulnerable(), plan.workDistancing()));
	std::unique_ptr<Environment> baseHospital(new Hospital(disease, hospitalBedsFiveK));
	std::unique_ptr<Environment> baseStore(new PublicSpace(disease, plan.storeIfSick(), plan.storeIfVulnerable(), plan.storeDistancing()));
	std::unique_ptr<Environment> baseSocial(new SocialGroup(disease, random, plan.socialIfSick(), plan.socialIfVulnerable(), plan.socialFrequency()));
	//The list of environments is filled with copies of the prototypes
	PopulateEnvironment(baseFamily, population / averageFamily);
	PopulateEnvironment(baseWorkplace, population / 20);
	PopulateEnvironment(baseHospital, population / 5000);
	//For simplicity, we assume each person has three public spaces they regularly visit and three social groups they regularly interact with
	PopulateEnvironment(baseStore, population / 500);
	PopulateEnvironment(baseStore, population / 500);
	PopulateEnvironment(baseStore, population / 500);
	PopulateEnvironment(baseSocial, population / 5);
	PopulateEnvironment(baseSocial, population / 5);
	PopulateEnvironment(baseSocial, population / 5);
}

int City::Update()
{
	//Cty::Update calls Environment::Update for each environment, which is a virtual function whose implementation depends on the particular environment
	for (std::list<std::unique_ptr<Environment>>::iterator i = environments.begin(); i != environments.end(); ++i)
	{
		i->get()->Update();
	}
	//After updating each environment, we update each person. Person::Update returns true if the person died, so while updating all the people we also count the new deaths for the day
	int newDeaths = 0;
	for (std::list<std::unique_ptr<Person>>::iterator i = people.begin(); i != people.end(); ++i)
	{
		if (i->get()->updatePerson())
		{
			newDeaths++;
		}
	}
	//Returns the number of deaths that occurred during this update to be written to the outputfile
	return newDeaths;
}

void City::PopulateEnvironment(std::unique_ptr<Environment> &baseEnvironment, int number)
{
	//We store the initial size of the environments container prior to adding more elements
	int initialSize = environments.size();
	for (int i = 0; i < number; i++)
	{
		environments.emplace_back(baseEnvironment.get()->Duplicate());
	}
	std::list<std::unique_ptr<Environment>>::iterator firstNewEnvironment = environments.begin();
	//Using the initial size, this creates an iterator to the first element that was added during this function
	for (int i = 0; i < initialSize; i++)
	{
		firstNewEnvironment++;
	}
	//We use random() to get an iterator to a random environment out of the environments added during this function
	int q = random() % number;
	std::list<std::unique_ptr<Environment>>::iterator j = firstNewEnvironment;
	for (int i = 0; i < q; i++)
	{
		j++;
	}
	for (std::list<std::unique_ptr<Person>>::iterator i = people.begin(); i != people.end(); ++i)
	{
		//Every person must be assigned to one environment during this function, and each environment must have at least one member
		//After each environment has a member, the remaining people are added randomly
		while ((j->get()->count() != 0 && (random() % 10) != 0))
		{
			//Skipping an environment to randomize which environment the i-th person gets placed into
			++j;
			if (j == environments.end())
			{
				j = firstNewEnvironment;
			}
		}
		//Get the raw pointer from j and add the ith person
		j->get()->addMember(*i);
		++j;
		if (j == environments.end())
		{
			j = firstNewEnvironment;
		}
	}
}
