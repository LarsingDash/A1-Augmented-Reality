#include "CPU.hpp"

#include <iostream>

CPU::CPU(const std::string& name, CpuSocketType socketType, const std::string& objectPath, const int tier)
	: PcPart(name, tier),
	  socketType(socketType),
	  objectPath(objectPath)
{
}

CPU::~CPU() = default;

std::string CPU::GetName() const
{
	return name;
}

void CPU::Display() const
{
	std::cout << "CPU: " << name << "\n";
	std::cout << "Socket Type: " << (socketType == CpuSocketType::INTEL ? "Intel" : "AMD") << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}

std::string CPU::GetObjectPath() const
{
	return objectPath;
}
