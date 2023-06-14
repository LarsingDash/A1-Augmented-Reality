#ifndef GPU_HPP
#define GPU_HPP

#include "PcPart.hpp"
#include <string>

class GPU : public PcPart {
public:
	std::string getName() const override;
	GPU(const std::string& name);
	~GPU();

	void display() const override;
};

#endif  