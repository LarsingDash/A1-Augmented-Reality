#ifndef RAM_HPP
#define RAM_HPP

#include "PcPart.hpp"
#include <string>

enum class RamSocketType {
	DDR3,
	DDR4
};

class RAM : public PcPart {
private:
	RamSocketType socketType;

public:
	RAM(const std::string& name, RamSocketType socketType);
	~RAM();
	std::string getName() const override;
	void display() const override;
};

#endif  
