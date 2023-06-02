#pragma once

#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

class GameObject
{
public:
	GameObject();
	void drawCube();
	void changeColor(glm::vec4 color);

};

