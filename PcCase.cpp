#include "PcCase.hpp"

#include <iostream>

PcCase::PcCase(const std::string& name) : PcPart(name) {}

PcCase::~PcCase() {
    for (PcPart* component : childComponents) {
        delete component;
    }
}

void PcCase::addComponent(PcPart* component) {
    childComponents.push_back(component);
}

void PcCase::removeComponent(PcPart* component) {
    auto it = std::find(childComponents.begin(), childComponents.end(), component);
    if (it != childComponents.end()) {
        childComponents.erase(it);
    }
}

void PcCase::display() const {
    std::cout << "PC Case: " << name << "\n";
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
    for (PcPart* component : childComponents) {
        component->display();
    }
}
