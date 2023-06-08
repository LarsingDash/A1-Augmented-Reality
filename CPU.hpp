#ifndef CPU_HPP
#define CPU_HPP

#include "PcPart.hpp"
#include <string>

enum class SocketType {
	INTEL,
	AMD
};

class CPU : public PcPart {
private:
	SocketType socketType;

public:
	CPU(const std::string& name, SocketType socketType);
	~CPU();
	std::string getName() const override;
	void display() const override;
};

#endif  
