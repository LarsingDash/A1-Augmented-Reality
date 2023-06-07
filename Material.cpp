#include "Material.h"
#include "tigl.h"

Material::Material()
= default;

void Material::SetAmbient(const glm::vec3 newAmbient)
{
	ambient = newAmbient;
}

void Material::SelectMaterial() const
{
	tigl::shader->setLightAmbient(1, ambient);
}
