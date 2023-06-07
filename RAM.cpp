#include "RAM.hpp"

#include <iostream>

RAM::RAM(const std::string& name, SocketType socketType) : PcPart(name), socketType(socketType) {}

RAM::~RAM() {}

void RAM::display() const {
	std::cout << "RAM: " << name << "\n";
	std::cout << "Socket Type: " << (socketType == SocketType::DDR3 ? "DDR3" : "DDR4") << "\n";
	std::cout << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
}
