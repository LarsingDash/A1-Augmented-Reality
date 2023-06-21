#include "PcPart.hpp"

PcPart::PcPart(const std::string& name, const int tier)
	: name(name),
	  tier(tier),
	  position(glm::vec3(0.0f))
{
}

PcPart::~PcPart()
{
}

void PcPart::SetPosition(const glm::vec3& pos)
{
	position = pos;
}

glm::vec3 PcPart::GetPosition() const
{
	return position;
}

int PcPart::GetTier() const
{
	return tier;
}
