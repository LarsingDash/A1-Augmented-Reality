#ifndef PCCASE_HPP
#define PCCASE_HPP

#include <vector>
#include "PcPart.hpp"

class PcCase : public PcPart {
private:
    std::vector<PcPart*> childComponents;
    std::string objectPath;

public:
    PcCase(const std::string& name, const std::string& objectPath);
    ~PcCase();

    void addComponent(PcPart* component);
    void removeComponent(PcPart* component);
    std::string getName() const override;
    std::string getObjectPath() const override;

    void display() const override;
};

#endif  // PCCASE_HPP
