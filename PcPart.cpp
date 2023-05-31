#include "PcPart.h"

// Constructor
PcPart::PcPart(const std::string& partName, bool required)
    : name(partName), isRequired(required) {}

// Getter for name
std::string PcPart::getName() const {
    return name;
}

// Setter for name
void PcPart::setName(const std::string& partName) {
    name = partName;
}

// Getter for isRequired
bool PcPart::getIsRequired() const {
    return isRequired;
}

// Setter for isRequired
void PcPart::setIsRequired(bool required) {
    isRequired = required;
}