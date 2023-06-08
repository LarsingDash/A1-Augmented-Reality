#ifndef MOTHERBOARD_HPP
#define MOTHERBOARD_HPP

#include <vector>
#include "PcPart.hpp"

enum class CpuSocketType {
	INTEL,
	AMD
};

class Motherboard : public PcPart {
private:
	std::vector<PcPart*> childComponents;
	CpuSocketType socketType;

public:
	Motherboard(const std::string& name, CpuSocketType socketType);
	~Motherboard();

	void addComponent(PcPart* component);
	void removeComponent(PcPart* component);

	void display() const override;
};

#endif 