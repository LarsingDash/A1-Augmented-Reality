#ifndef PC_PART_H
#define PC_PART_H

#include <string>

class PcPart {
private:
    std::string name;
    bool isRequired;

public:
    PcPart(const std::string& partName, bool required);

    std::string getName() const;

    void setName(const std::string& partName);

    bool getIsRequired() const;

    void setIsRequired(bool required);
};

#endif