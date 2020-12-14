#include "Manager.hpp"
#include <iostream>

Manager::Manager(std::string inputDataFilename, std::string planFilename, std::string outputFilename)
{
	//The basic values describing the disease and the nature of the city do not vary and are members of the class, so we read them from the datafile at initialization
	std::ifstream cityInputs(inputDataFilename);
	cityInputs >> population;
	cityInputs >> averageFamily;
	cityInputs >> averageWorkplace;
	cityInputs >> hospitalBedsFiveK;
	cityInputs >> incubationDays;
	cityInputs >> recoveryDays;
	cityInputs >> deathRate;
	cityInputs >> infectionChance;
	cityInputs >> symptomaticChance;
	planFile = planFilename;
	outputFile = outputFilename;
}

void Manager::runExperiment()
{
	//Preparing input and output filestreams
	std::ifstream planInputs(planFile);
	std::ofstream outputs(outputFile);
	int iterations{0};
	int sampleSize{0};
	//The first value in the PlanData file is the number of simulations the program should run
	planInputs >> iterations;
	planInputs >> sampleSize;
	std::vector<double> values;
	try
	{
		//The parameters of the disease remain constant throughout all the simulations
		Disease disease(incubationDays, recoveryDays, deathRate, infectionChance, symptomaticChance);
		for (int i = 0; i < iterations; i++)
		{
			values.assign(9, 0);
			for (int j = 0; j < 9; j++)
			{
				planInputs >> values[j];
			}
			try
			{
				int deaths{0};
				for (int k = 0; k < sampleSize; k++)
				{
					//We use the inputs to generate the next plan to test and use the plan to initialize a new city
					Plan currentPlan(values);
					City testCity(disease, population, averageFamily, averageWorkplace, hospitalBedsFiveK, currentPlan);
					for (int q = 0; q < 200; q++)
					{
						//We count the total deaths to report in the output file, along with the plan parameters that produced those values
						deaths += testCity.Update();
					}
				}
				for (int j = 0; j < 9; j++)
				{
					outputs << values[j] << ", ";
				}
				//The output to be printed is the average of the total deaths for this trial over all the samples
				outputs << (int)round((double)deaths / sampleSize) << "\n";
				std::cout << i + 1 << " out of " << iterations << " simulations completed.\n";
			}
			catch (Plan::invalidInputs &e)
			{
				std::cout << "Attempted to initialize response plan with invalid inputs.\n";
			}
		}
	}
	catch (Disease::invalidInputs &e)
	{
		std::cout << "Attempted to initialize disease with invalid inputs.\n";
	}
}
