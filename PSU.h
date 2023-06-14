#ifndef PSU_HPP
#define PSU_HPP

#include "PcPart.hpp"
#include <string>

class PSU : public PcPart {
public:
    PSU(const std::string& name, const std::string& objectPath);
    ~PSU();

    std::string getName() const override;
    std::string getObjectPath() const override;
    void display() const override;

private:
    std::string objectPath;

};

#endif // PSU_HPP
