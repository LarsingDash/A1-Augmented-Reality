#include "PcCase.hpp"

#include <iostream>

PcCase::PcCase(const std::string& name, const std::string& objectPath) : PcPart(name), objectPath(objectPath) {}

PcCase::~PcCase() {
    for (PcPart* component : childComponents) {
        delete component;
    }
}

std::string PcCase::getName() const {
    return name;
}

std::string PcCase::getObjectPath() const {
    return objectPath;
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
