#include "GPU.hpp"

#include <iostream>

GPU::GPU(const std::string& name) : PcPart(name)
{
}

GPU::~GPU()
{
}

std::string GPU::getName() const {
	return name;
}

void GPU::display() const
{
	std::cout << "GPU: " << name << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
