#include "PcPart.hpp"

PcPart::PcPart(const std::string& name) : name(name), position(glm::vec3(0.0f)) {}

PcPart::~PcPart() {}

void PcPart::setPosition(const glm::vec3& pos) {
	position = pos;
}

glm::vec3 PcPart::getPosition() const {
	return position;
}
