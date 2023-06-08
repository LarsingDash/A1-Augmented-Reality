#include "Motherboard.hpp"

#include <iostream>

Motherboard::Motherboard(const std::string& name, CpuSocketType socketType)
    : PcPart(name), socketType(socketType) {}

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
    std::cout << "Socket Type: " << (socketType == CpuSocketType::INTEL ? "Intel" : "AMD") << "\n";
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
    for (PcPart* component : childComponents) {
        component->display();
    }
}
