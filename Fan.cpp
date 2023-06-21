#include "Fan.hpp"

#include <iostream>

#include "PcPart.hpp"

Fan::Fan(const std::string& name, const std::string& objectPath, const int tier)
	: PcPart(name, tier),
	  objectPath(objectPath)
{
}

Fan::~Fan()
{
}

std::string Fan::GetName() const
{
	return name;
}

std::string Fan::GetObjectPath() const
{
	return objectPath;
}


void Fan::Display() const
{
	std::cout << "Fan: " << name << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
