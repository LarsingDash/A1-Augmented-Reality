#ifndef PSU_HPP
#define PSU_HPP

#include "PcPart.hpp"
#include <string>

class PSU : public PcPart {
public:
    PSU(const std::string& name, const std::string& objectPath);
    ~PSU();

    std::string getName() const override;
    void display() const override;
};

#endif // PSU_HPP
