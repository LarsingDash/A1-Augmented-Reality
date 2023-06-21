#pragma once

#include "Texture.h"

#include <string>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

class Material
{
	public:
		//Constructor
		Material(const std::string& matName);

		//Setters
		void SetTexture(const std::string& texPath, const std::string& texName, const std::string& objectDir);
		void SetMaterialColor(const glm::vec4 color);

		//Bind material
		void SelectMaterial() const;

		//Getter
		std::string GetName();

	private:
		std::string name;

		std::vector<Texture*> textures;
		glm::vec4 diffuse{};
};

static Texture* baseTexture = nullptr;
