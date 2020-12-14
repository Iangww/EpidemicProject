#include "Environment.hpp"
class Family : public Environment
{
public:
	Family(Disease &);
	void Update();
	Environment *Duplicate();
};
