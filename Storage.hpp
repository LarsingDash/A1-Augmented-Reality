#ifndef STORAGE_HPP
#define STORAGE_HPP

#include "PcPart.hpp"
#include <string>

class Storage : public PcPart {
public:
    Storage(const std::string& name, const std::string& objectPath, const int tier);
    ~Storage();

    std::string getName() const override;
    std::string getObjectPath() const override;
    void display() const override;

private:
    std::string objectPath;

};

#endif  // STORAGE_HPP
