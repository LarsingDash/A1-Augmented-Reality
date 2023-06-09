#ifndef RAM_HPP
#define RAM_HPP

#include "PcPart.hpp"
#include <string>

enum class SocketType {
	DDR3,
	DDR4
};

class RAM : public PcPart {
private:
	SocketType socketType;

public:
	RAM(const std::string& name, SocketType socketType);
	~RAM();

	void display() const override;
};

#endif  
