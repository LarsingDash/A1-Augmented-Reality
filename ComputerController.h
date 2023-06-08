#pragma once
#include <vector>
#include "GameObject.h"
class ComputerController
{
public:
	ComputerController(bool isDrawing);
	void handleDraw(const glm::vec3& position, const glm::mat4& rotation);

	void setIsDrawing(bool isDrawing);
	std::vector<GameObject> objects;

private:
	bool isDrawing = false;
};

