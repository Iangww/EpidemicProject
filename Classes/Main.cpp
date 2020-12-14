#include <iostream>
#include "Manager.hpp"

int main(int argc, char **argv)
{
    //Print some documentation if the wrong number of arguments are passed
    if (argc != 4)
    {
        std::cout << "This program requires as arguments three strings. The first should be the name of the file containing the parameters of the city and the disease, ";
        std::cout << "in the order population, averageFamilySize, averageWorkplaceSize, hospitalBedsPer5KPeople, incubationDays, recoveryDays, deathRate, infectionRate, symptomRate.";
        std::cout << "The second string should be the name of the file containing the parameters of the response plans. The first entry in that file must be the number of response ";
        std::cout << "plans to be tested and the second should be the number of times to test each plan. After that, the file should contain parameters for response plans where each plan ";
        std::cout << "is represented by parameters, in order, workIfSick, workIfVulnerable, workDistance, storeIfSick, storeIfVulnerable, storeDistance, socialIfSick, ";
        std::cout << "socialIfVulnerable, socialFrequency. The final string should be the name of a blank file to write the output to.";
    }
    else
    {
        Manager manager(argv[1], argv[2], argv[3]);
        manager.runExperiment();
    }
}