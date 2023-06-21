#ifndef PCPART_HPP
#define PCPART_HPP

#include <string>
#include <glm/glm.hpp>

class PcPart
{
	protected:
		std::string name;
		int tier;
		glm::vec3 position;
		std::string objectPath;

	public:
		PcPart(const std::string& name, int tier);
		virtual ~PcPart();

		// Getter and setter for position
		void SetPosition(const glm::vec3& pos);
		virtual std::string GetObjectPath() const = 0;

		glm::vec3 GetPosition() const;
		int GetTier() const;
		virtual std::string GetName() const = 0;
		virtual void Display() const = 0;
};

#endif  // PCPART_HPP
