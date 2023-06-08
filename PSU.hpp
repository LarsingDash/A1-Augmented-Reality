#ifndef PSU_HPP
#define PSU_HPP

#include "PcPart.hpp"
#include <string>

class PSU : public PcPart {
public:
	PSU(const std::string& name);
	~PSU();
	std::string getName() const override;

	void display() const override;
};

#endif  
