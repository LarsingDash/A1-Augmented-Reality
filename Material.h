#pragma once

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture.h"
#include <vector>

class Material
{
	public:
		Material(const std::string& matName);
		void SetTexture(const std::string& texPath, const std::string& texName, const std::string& objectDir);
		void SetMaterialColor(const glm::vec4 color);

		void SelectMaterial() const;

		std::string GetName();

	private:
		std::string name;
		std::vector<Texture*> textures;

		glm::vec4 diffuse{};
};

static Texture* baseTexture = nullptr;
