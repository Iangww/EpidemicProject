#include "Environment.hpp"
class PublicSpace : public Environment
{
public:
	PublicSpace(Disease &, double, double, double);
	void Update();
	Environment *Duplicate();

private:
	double distanceLevel;
	double stayHomeIfSick;
	double stayHomeIfVulnerable;
};
