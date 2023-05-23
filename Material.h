#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <string>

class Material
{
	public:
		Material();

		void SetAmbient(const glm::vec3 newAmbient);
		void SelectMaterial() const;

		std::string name;

	private:
		glm::vec3 ambient{};
};
