#ifndef CPU_HPP
#define CPU_HPP

#include "PcPart.hpp"
#include <string>

enum class CpuSocketType {
	INTEL,
	AMD
};

class CPU : public PcPart {
private:
	CpuSocketType socketType;

public:
	CPU(const std::string& name, CpuSocketType socketType, const std::string& objectPath);
	~CPU();
	std::string getName() const override;
	void display() const override;
};

#endif  
