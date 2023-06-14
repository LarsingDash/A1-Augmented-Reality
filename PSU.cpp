#include "PSU.h"


#include <iostream>

PSU::PSU(const std::string& name, const std::string& objectPath) : PcPart(name) {}

PSU::~PSU() {}
std::string PSU::getName() const {
	return name;
}
std::string PSU::getObjectPath() const {
	return objectPath;
}
void PSU::display() const {
	std::cout << "PSU: " << name << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
