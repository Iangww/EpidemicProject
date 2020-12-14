#pragma once
#include "Person.hpp"
#include <list>
#include <memory>

class Environment
{
public:
	int count() const;
	virtual void Update() = 0;
	virtual Environment *Duplicate() = 0;
	void addMember(const std::unique_ptr<Person> &newVisitor);
	Environment(Disease &);
	~Environment();

protected:
	std::list<Person *> visitors;
	Disease &disease;
};