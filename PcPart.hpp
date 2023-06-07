#ifndef PCPART_HPP
#define PCPART_HPP

#include <string>
#include <glm/glm.hpp>

class PcPart {
protected:
  std::string name;
  glm::vec3 position;

public:
  PcPart(const std::string& name);
  virtual ~PcPart();

  // Getter and setter for position
  void setPosition(const glm::vec3& pos);
  glm::vec3 getPosition() const;

  virtual void display() const = 0;
};

#endif  // PCPART_HPP
