#ifndef PCCASE_HPP
#define PCCASE_HPP

#include <vector>
#include "PcPart.hpp"

class PcCase : public PcPart {
private:
	std::vector<PcPart*> childComponents;

public:
	PcCase(const std::string& name);
	~PcCase();

	void addComponent(PcPart* component);
	void removeComponent(PcPart* component);

	void display() const override;
};

#endif  
