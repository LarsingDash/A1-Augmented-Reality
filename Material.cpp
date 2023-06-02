#include "Material.h"
#include "tigl.h"
#include "Texture.h"

#include <iostream>

Material::Material(const std::string& matName)
{
	name = matName;
}

void Material::SetTexture(const std::string& texturePath)
{
	tex = texturePath;
}

void Material::SetMaterialColor(const glm::vec4 color)
{
	diffuse = color;
	std::cout << "----------- Diffuse:" << std::endl;
	std::cout << diffuse.x << std::endl;
	std::cout << diffuse.y << std::endl;
	std::cout << diffuse.z << std::endl;
	std::cout << diffuse.a << std::endl;
}

void Material::SelectMaterial() const
{
	if (!tex.empty())
	{
		tigl::shader->enableColor(false);
		tigl::shader->enableTexture(true);
		tigl::shader->enableColorMult(false);

		Texture texture = Texture(tex);
		texture.bind();
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
