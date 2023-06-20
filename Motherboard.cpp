#include "Motherboard.hpp"

#include <iostream>

#include "RAM.hpp"

Motherboard::Motherboard(const std::string& name, CpuSocketType socketType, RamSocketType ramSocketType, const std::string& objectPath)
    : PcPart(name), socketType(socketType), ramSocketType(ramSocketType), objectPath(objectPath) {}

Motherboard::~Motherboard() {
    for (PcPart* component : childComponents) {
        delete component;
    }
}

void Motherboard::addComponent(PcPart* component) {
    childComponents.push_back(component);
}

void Motherboard::removeComponent(PcPart* component) {
    auto it = std::find(childComponents.begin(), childComponents.end(), component);
    if (it != childComponents.end()) {
        childComponents.erase(it);
    }
}

void Motherboard::display() const {
    std::cout << "Motherboard: " << name << "\n";
    std::cout << "CPU Socket Type: " << (socketType == CpuSocketType::INTEL ? "Intel" : "AMD") << "\n";
    std::cout << "RAM Socket Type: " << (ramSocketType == RamSocketType::DDR3 ? "DDR3" : "DDR4") << "\n";
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
    for (PcPart* component : childComponents) {
        component->display();
    }
}

std::string Motherboard::getName() const {
    return name;
}

std::string Motherboard::getObjectPath() const {
    return objectPath;
}
