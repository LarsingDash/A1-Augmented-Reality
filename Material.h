#pragma once

#include <string>

#include "Texture.h"

class Material
{
	public:
		Material(const std::string& name);

		void SetTexture(const std::string& texture);
		void SelectMaterial() const;

		std::string GetName();

	private:
		std::string name;
		std::string tex;
		// Texture texture;
};
