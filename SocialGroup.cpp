#include "SocialGroup.hpp"

SocialGroup::SocialGroup(Disease &inputDisease, std::mt19937 &inputRandom, double inputSick, double inputVulnerable, double inputFrequency) : Environment{inputDisease}, random{inputRandom}, stayHomeIfSick{inputSick}, stayHomeIfVulnerable{inputVulnerable}, visitFrequency{inputFrequency} {}

void SocialGroup::Update()
{
    //Social groups only meet on randomly distributed days with a set frequency
    if (random() / random.max() < visitFrequency)
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
                    uninfectedProbability *= 1 - disease.getInfectionChance();
                }
                else
                {
                    uninfectedProbability *= 1 - stayHomeIfSick * disease.getInfectionChance();
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
}

Environment *SocialGroup::Duplicate()
{
    //This function is used to create many identical copies of the prototype SocialGroup when populating the city environment list
    Environment *output = new SocialGroup(disease, random, stayHomeIfSick, stayHomeIfVulnerable, visitFrequency);
    return output;
}