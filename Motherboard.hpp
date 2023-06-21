#ifndef MOTHERBOARD_HPP
#define MOTHERBOARD_HPP

#include <vector>
#include "PcPart.hpp"
#include "RAM.hpp"
#include "CPU.hpp"


class Motherboard : public PcPart {
private:
    std::vector<PcPart*> childComponents;
    std::string objectPath;

public:
    CpuSocketType socketType;
    RamSocketType ramSocketType;
    Motherboard(const std::string& name, CpuSocketType socketType, RamSocketType ramSocketType, const std::string& objectPath, const int tier);
    ~Motherboard();

    void addComponent(PcPart* component);
    void removeComponent(PcPart* component);
    std::string getObjectPath() const override;

    void display() const override;
    std::string getName() const override;
};

#endif  // MOTHERBOARD_HPP
