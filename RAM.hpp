#ifndef RAM_HPP
#define RAM_HPP

#include "PcPart.hpp"
#include <string>

enum class RamSocketType {
    DDR3,
    DDR4
};

class RAM : public PcPart {
private:
    RamSocketType socketType;
    std::string objectPath;

public:
    RAM(const std::string& name, RamSocketType socketType, const std::string& objectPath);
    ~RAM();

    std::string getName() const override;
    std::string getObjectPath() const override;
    void display() const override;
};

#endif  // RAM_HPP
