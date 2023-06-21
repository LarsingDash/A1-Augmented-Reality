#include "Motherboard.hpp"

#include <iostream>

#include "RAM.hpp"

Motherboard::Motherboard(const std::string& name, CpuSocketType socketType, RamSocketType ramSocketType,
                         const std::string& objectPath, const int tier)
	: PcPart(name, tier),
	  socketType(socketType),
	  ramSocketType(ramSocketType),
	  objectPath(objectPath)
{
}

Motherboard::~Motherboard()
{
	for (PcPart* component : childComponents)
	{
		delete component;
	}
}

void Motherboard::AddComponent(PcPart* component)
{
	childComponents.push_back(component);
}

void Motherboard::RemoveComponent(PcPart* component)
{
	auto it = std::find(childComponents.begin(), childComponents.end(), component);
	if (it != childComponents.end())
	{
		childComponents.erase(it);
	}
}

void Motherboard::Display() const
{
	std::cout << "Motherboard: " << name << "\n";
	std::cout << "CPU Socket Type: " << (socketType == CpuSocketType::INTEL ? "Intel" : "AMD") << "\n";
	std::cout << "RAM Socket Type: " << (ramSocketType == RamSocketType::DDR3 ? "DDR3" : "DDR4") << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
	for (PcPart* component : childComponents)
	{
		component->Display();
	}
}

std::string Motherboard::GetName() const
{
	return name;
}

std::string Motherboard::GetObjectPath() const
{
	return objectPath;
}
