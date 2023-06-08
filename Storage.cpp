#include "Storage.hpp"

#include <iostream>

Storage::Storage(const std::string& name) : PcPart(name) {}

Storage::~Storage() {}
std::string Storage::getName() const {
	return name;
}
void Storage::display() const {
	std::cout << "Storage: " << name << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
