#pragma once
#include <vector>
#include "GameObject.h"
class ComputerController
{
public:
	ComputerController(GameObject currentObject, bool isDrawing);
	void handleDraw();
	void setCurrentObject(GameObject newObject);
	void drawCurrentObject();
	void setIsDrawing(bool isDrawing);

private:
	GameObject currentObject;
	std::vector<GameObject> objects;
	//bool isDrawing;
};

