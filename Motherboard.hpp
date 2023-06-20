#ifndef MOTHERBOARD_HPP
#define MOTHERBOARD_HPP

#include <vector>
#include "PcPart.hpp"
#include "RAM.hpp"

enum class MbuSocketType {
    INTEL,
    AMD
};

class Motherboard : public PcPart {
private:
    std::vector<PcPart*> childComponents;
    MbuSocketType socketType;
    RamSocketType ramSocketType;
    std::string objectPath;

public:
    Motherboard(const std::string& name, MbuSocketType socketType, RamSocketType ramSocketType, const std::string& objectPath);
    ~Motherboard();

    void addComponent(PcPart* component);
    void removeComponent(PcPart* component);
    std::string getObjectPath() const override;

    void display() const override;
    std::string getName() const override;
};

#endif  // MOTHERBOARD_HPP
