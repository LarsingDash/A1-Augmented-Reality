#include "RAM.hpp"

#include <iostream>

RAM::RAM(const std::string& name, RamSocketType socketType) : PcPart(name), socketType(socketType) {}

RAM::~RAM() {}
std::string RAM::getName() const {
	return name;
}
void RAM::display() const {
	std::cout << "RAM: " << name << "\n";
	std::cout << "Socket Type: " << (socketType == RamSocketType::DDR3 ? "DDR3" : "DDR4") << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
