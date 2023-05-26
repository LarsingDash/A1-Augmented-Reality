#include "Material.h"

#include <iostream>

Material::Material(const std::string& matName)
{
	name = matName;
}

void Material::SetTexture(const std::string& texturePath)
{
	tex = texturePath;
}

void Material::SelectMaterial() const
{
	Texture texture = Texture(tex);
	texture.bind();
}

std::string Material::GetName()
{
	return name;
}
