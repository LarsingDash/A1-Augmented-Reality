#ifndef MOTHERBOARD_HPP
#define MOTHERBOARD_HPP

#include <vector>
#include "PcPart.hpp"

enum class MbuSocketType {
	INTEL,
	AMD
};

class Motherboard : public PcPart {
private:
	std::vector<PcPart*> childComponents;
	MbuSocketType socketType;

public:
	Motherboard(const std::string& name, MbuSocketType socketType, const std::string& objectPath);
	~Motherboard();

	void addComponent(PcPart* component);
	void removeComponent(PcPart* component);

	void display() const override;
	std::string getName() const override;
};

#endif 