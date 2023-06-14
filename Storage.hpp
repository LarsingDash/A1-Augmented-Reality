#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "PcPart.hpp"
#include <string>

class Storage : public PcPart {
public:
	Storage(const std::string& name, const std::string& objectPath);
	~Storage();
	std::string getName() const override;

	void display() const override;
};

#endif  
