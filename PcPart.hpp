#ifndef PCPART_HPP
#define PCPART_HPP

#include <string>
#include <glm/glm.hpp>

class PcPart {
protected:
  std::string name;
  glm::vec3 position;
  std::string objectPath;

public:
  PcPart(const std::string& name);
  virtual ~PcPart();

  // Getter and setter for position
  void setPosition(const glm::vec3& pos);
  virtual std::string getObjectPath() const = 0;

  glm::vec3 getPosition() const;
  virtual std::string getName() const = 0;
  virtual void display() const = 0;
};

#endif  // PCPART_HPP
