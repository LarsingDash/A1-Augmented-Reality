#include "CPU.hpp"

#include <iostream>

CPU::CPU(const std::string& name, CpuSocketType socketType, const std::string& objectPath) : PcPart(name), socketType(socketType), objectPath(objectPath) {}

CPU::~CPU() {}
std::string CPU::getName() const{
	return name;
}
void CPU::display() const {
	std::cout << "CPU: " << name << "\n";
	std::cout << "Socket Type: " << (socketType == CpuSocketType::INTEL ? "Intel" : "AMD") << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
std::string CPU::getObjectPath() const {
	return objectPath;
}

