#ifndef GPU_HPP
#define GPU_HPP

#include "PcPart.hpp"
#include <string>

class GPU : public PcPart {
public:
    GPU(const std::string& name, const std::string& objectPath, const int tier);
    ~GPU();

    std::string getName() const override;
    std::string getObjectPath() const override;
    void display() const override;

private:
    std::string objectPath;

};

#endif  // GPU_HPP
