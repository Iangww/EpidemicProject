class Disease
{
public:
	Disease(int, int, double, double, double);
	int getIncubationDays() const;
	int getRecoveryDays() const;
	double getDeathRate() const;
	double getInfectionChance() const;
	double getSymptomaticChance() const;
	class invalidInputs
	{
	};

private:
	int incubationDays;
	int recoveryDays;
	double deathRate;
	double infectionChance;
	double symptomaticChance;
};
