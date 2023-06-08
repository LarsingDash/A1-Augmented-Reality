#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "PcPart.hpp"
#include <string>

class Storage : public PcPart {
public:
	Storage(const std::string& name);
	~Storage();

	void display() const override;
};

#endif  
