#include "Material.h"
#include "tigl.h"

#include <iostream>

Material::Material(const std::string& matName)
{
	name = matName;
}

void Material::SetTexture(const std::string& texPath, const std::string& texName, const std::string& objectDir)
{
	textures.clear();

	if (texName == "PC.png")
	{
		if (baseTexture == nullptr)
		{
			baseTexture = new Texture(objectDir + "/objects/PC.png");
		}

		textures.push_back(baseTexture);
	}
	else textures.push_back(new Texture(texPath + texName));
}

void Material::SetMaterialColor(const glm::vec4 color)
{
	diffuse = color;
}

void Material::SelectMaterial() const
{
	if (!textures.empty())
	{
		tigl::shader->enableColor(false);
		tigl::shader->enableTexture(true);
		tigl::shader->enableColorMult(false);

		textures[0]->bind();
	}
	else
	{
		tigl::shader->enableColor(false);
		tigl::shader->enableTexture(false);
		tigl::shader->enableColorMult(true);

		tigl::shader->setColorMult(diffuse);
	}
}

std::string Material::GetName()
{
	return name;
}
