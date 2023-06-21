#include "Storage.hpp"

#include <iostream>

Storage::Storage(const std::string& name, const std::string& objectPath, const int tier) : PcPart(name, tier), objectPath(objectPath) {}

Storage::~Storage() {}

std::string Storage::getName() const {
    return name;
}

std::string Storage::getObjectPath() const {
    return objectPath;
}


void Storage::display() const {
    std::cout << "Storage: " << name << "\n";
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
