#include "Environment.hpp"
#include "Family.hpp"
#include "PublicSpace.hpp"
#include "Hospital.hpp"
#include "SocialGroup.hpp"
#include <string>

class Plan
{
public:
	class invalidInputs
	{
	};
	double workIfSick() { return values[0]; }
	double workIfVulnerable() { return values[1]; }
	double workDistancing() { return values[2]; }
	double storeIfSick() { return values[3]; }
	double storeIfVulnerable() { return values[4]; }
	double storeDistancing() { return values[5]; }
	double socialIfSick() { return values[6]; }
	double socialIfVulnerable() { return values[7]; }
	double socialFrequency() { return values[8]; }
	Plan(std::vector<double> input) : values{input}
	{
		if (values.size() != 9)
		{
			throw invalidInputs{};
		}
		for (int i = 0; i < 9; i++)
		{
			if (values[i] < 0 || values[i] > 1)
			{
				throw invalidInputs{};
			}
		}
	}

private:
	std::vector<double> values;
};

class City
{
public:
	City(Disease &, int, double, double, int, Plan &);
	int Update();

private:
	void PopulateEnvironment(std::unique_ptr<Environment> &, int);
	Disease &disease;
	Plan plan;
	int population;
	double averageFamily;
	double averageWorkplace;
	int hospitalBedsFiveK;
	std::list<std::unique_ptr<Person>> people;
	std::list<std::unique_ptr<Environment>> environments;
	std::mt19937 random;
};
