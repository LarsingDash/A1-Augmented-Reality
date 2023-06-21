#include "GPU.hpp"

#include <iostream>

GPU::GPU(const std::string& name, const std::string& objectPath, const int tier) : PcPart(name, tier), objectPath(objectPath) {}

GPU::~GPU() {}

std::string GPU::getName() const {
    return name;
}

std::string GPU::getObjectPath() const {
    return objectPath;
}

void GPU::display() const {
    std::cout << "GPU: " << name << "\n";
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
