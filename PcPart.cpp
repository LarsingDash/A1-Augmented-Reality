#include "PcPart.h"

PcPart::PcPart(const std::string& partName, bool required)
    : name(partName), isRequired(required) {}

std::string PcPart::getName() const {
    return name;
}

void PcPart::setName(const std::string& partName) {
    name = partName;
}

bool PcPart::getIsRequired() const {
    return isRequired;
}

void PcPart::setIsRequired(bool required) {
    isRequired = required;
}