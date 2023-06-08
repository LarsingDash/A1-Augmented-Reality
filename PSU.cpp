#include "PSU.hpp"


#include <iostream>

PSU::PSU(const std::string& name) : PcPart(name) {}

PSU::~PSU() {}
std::string PSU::getName() const {
	return name;
}
void PSU::display() const {
	std::cout << "PSU: " << name << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
