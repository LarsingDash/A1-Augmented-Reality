#include "Storage.hpp"

#include <iostream>

Storage::Storage(const std::string& name) : PcPart(name) {}

Storage::~Storage() {}

void Storage::display() const {
	std::cout << "Storage: " << name << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
