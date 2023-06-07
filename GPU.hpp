#ifndef GPU_HPP
#define GPU_HPP

#include "PcPart.hpp"
#include <string>

class GPU : public PcPart {
public:
	GPU(const std::string& name);
	~GPU();

	void display() const override;
};

#endif  