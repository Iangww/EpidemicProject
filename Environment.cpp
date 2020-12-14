#include "Environment.hpp"

int Environment::count() const
{
	return visitors.size();
}

void Environment::addMember(const std::unique_ptr<Person> &newVisitor)
{
	//Takes a reference to a unique_ptr<Person> and adds the raw pointer to the list of members.
	visitors.push_back(newVisitor.get());
}

Environment::Environment(Disease &inputDisease) : disease{inputDisease}
{
}

Environment::~Environment()
{
}
