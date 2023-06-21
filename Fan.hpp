#ifndef FAN_FPP
#define FAN_HPP

#include "PcPart.hpp"
#include <string>

class Fan : public PcPart {
public:
    Fan(const std::string& name, const std::string& objectPath, const int tier);
    ~Fan();

    std::string getName() const override;
    std::string getObjectPath() const override;
    void display() const override;

private:
    std::string objectPath;

};

#endif  
