#include "GPU.hpp"

#include <iostream>

GPU::GPU(const std::string& name, const std::string& objectPath, const int tier)
	: PcPart(name, tier),
	  objectPath(objectPath)
{
}

GPU::~GPU()
{
}

std::string GPU::GetName() const
{
	return name;
}

std::string GPU::GetObjectPath() const
{
	return objectPath;
}

void GPU::Display() const
{
	std::cout << "GPU: " << name << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
