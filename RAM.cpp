#include "RAM.hpp"

#include <iostream>

RAM::RAM(const std::string& name, RamSocketType socketType, const std::string& objectPath)
    : PcPart(name), socketType(socketType), objectPath(objectPath) {}

RAM::~RAM() {}

std::string RAM::getName() const {
    return name;
}

std::string RAM::getObjectPath() const {
    return objectPath;
}

void RAM::display() const {
    std::cout << "RAM: " << name << "\n";
    std::cout << "Socket Type: " << (socketType == RamSocketType::DDR3 ? "DDR3" : "DDR4") << "\n";
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
