#include "Disease.hpp"
#include <random>

class Person
{
public:
	int getInfectedDays() const;
	int getHealth() const;
	bool isInfectious() const;
	bool isSymptomatic() const;
	void infectChance(double);
	void improveCondition();
	bool updatePerson();
	Person(int, std::mt19937 &, Disease &);

private:
	Disease &disease;
	int overallHealth;
	int infectedDays;
	std::mt19937 &random;
	bool alive;
	bool symptomatic;
};