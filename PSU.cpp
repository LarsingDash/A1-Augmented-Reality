#include "PSU.h"


#include <iostream>

PSU::PSU(const std::string& name, const std::string& objectPath, const int tier)
	: PcPart(name, tier),
	  objectPath(objectPath)
{
}

PSU::~PSU()
{
}

std::string PSU::GetName() const
{
	return name;
}

std::string PSU::GetObjectPath() const
{
	return objectPath;
}

void PSU::Display() const
{
	std::cout << "PSU: " << name << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
