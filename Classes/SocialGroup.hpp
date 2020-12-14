#include "Environment.hpp"
class SocialGroup : public Environment
{
public:
    SocialGroup(Disease &, std::mt19937 &, double, double, double);
    void Update();
    Environment *Duplicate();

private:
    std::mt19937 &random;
    double stayHomeIfSick;
    double stayHomeIfVulnerable;
    double visitFrequency;
};