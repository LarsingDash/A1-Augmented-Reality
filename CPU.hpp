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
	std::string objectPath;
public:
    CpuSocketType socketType;
    CPU(const std::string& name, CpuSocketType socketType, const std::string& objectPath, const int tier);
    ~CPU();
    std::string getName() const override;
    void display() const override;
    std::string getObjectPath() const override; 
};
#endif  
