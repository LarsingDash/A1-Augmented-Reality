#ifndef PC_PART_H
#define PC_PART_H

#include <string>

class PcPart {
private:
    std::string name;
    bool isRequired;

public:
    // Constructor
    PcPart(const std::string& partName, bool required);

    // Getter for name
    std::string getName() const;

    // Setter for name
    void setName(const std::string& partName);

    // Getter for isRequired
    bool getIsRequired() const;

    // Setter for isRequired
    void setIsRequired(bool required);
};

#endif