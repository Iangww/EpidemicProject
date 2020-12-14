#include "Environment.hpp"
class Hospital : public Environment
{
public:
    Hospital(Disease &, int);
    void Update();
    Environment *Duplicate();

private:
    int totalBeds;
};