#include <iostream>
#include <string>

class PcPart {
private:
    std::string name;
    bool isRequired;

public:
    // Constructor
    PcPart(const std::string& partName, bool required)
        : name(partName), isRequired(required) {}

    // Getter for name
    std::string getName() const {
        return name;
    }

    // Setter for name
    void setName(const std::string& partName) {
        name = partName;
    }

    // Getter for isRequired
    bool getIsRequired() const {
        return isRequired;
    }

    // Setter for isRequired
    void setIsRequired(bool required) {
        isRequired = required;
    }
};