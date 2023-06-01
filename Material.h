#pragma once

#include <string>
#include <glm/gtc/matrix_transform.hpp>

class Material
{
	public:
		Material(const std::string& name);
		void SetTexture(const std::string& texture);
		void SetMaterialColor(const glm::vec4 color);

		void SelectMaterial() const;

		std::string GetName();

	private:
		std::string name;
		std::string tex;

		glm::vec4 diffuse;
};
