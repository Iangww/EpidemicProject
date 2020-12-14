#include "Hospital.hpp"

Hospital::Hospital(Disease &inputDisease, int bedsInput) : Environment{inputDisease}, totalBeds{bedsInput} {}

void Hospital::Update()
{
    //A single hospital is capable of supporting a fixed number of sick people each day
    int beds = totalBeds;
    for (std::list<Person *>::iterator i = visitors.begin(); i != visitors.end(); ++i)
    {
        if (beds > 0 && (*i)->isSymptomatic() && (*i)->getHealth() < 4)
        {
            (*i)->improveCondition();
            beds--;
        }
    }
}

Environment *Hospital::Duplicate()
{
    //This function is used to create many identical copies of the prototype publicSpace when populating the city environment list
    Environment *output = new Hospital(disease, totalBeds);
    return output;
}