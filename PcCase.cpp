#include "PcCase.hpp"

#include <iostream>

PcCase::PcCase(const std::string& name, const std::string& objectPath, const int tier) : PcPart(name, tier), objectPath(objectPath) {}

PcCase::~PcCase() {
    for (PcPart* component : childComponents) {
        delete component;
    }
}

std::string PcCase::GetName() const {
    return name;
}

std::string PcCase::GetObjectPath() const {
    return objectPath;
}

void PcCase::AddComponent(PcPart* component) {
    childComponents.push_back(component);
}

void PcCase::RemoveComponent(PcPart* component) {
    auto it = std::find(childComponents.begin(), childComponents.end(), component);
    if (it != childComponents.end()) {
        childComponents.erase(it);
    }
}

void PcCase::Display() const {
    std::cout << "PC Case: " << name << "\n";
    std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
    for (PcPart* component : childComponents) {
        component->Display();
    }
}
