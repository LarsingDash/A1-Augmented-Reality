#include <iostream>
#include "ComputerController.h"

bool isDrawing;

ComputerController::ComputerController(GameObject currentObject, bool newIsDrawing) {
	ComputerController::currentObject = currentObject;
	isDrawing = newIsDrawing;
}

void ComputerController::setIsDrawing(bool newIsDrawing) {
	isDrawing = newIsDrawing;
}

void ComputerController::handleDraw() {
	std::cout << "IsDrawing: " << isDrawing << std::endl;
	if (isDrawing) {
		drawCurrentObject();
	}
}

void ComputerController::setCurrentObject(GameObject currentObject) {
	ComputerController::currentObject = currentObject;
}

void ComputerController::drawCurrentObject() {
	ComputerController::currentObject.Draw(glm::mat4(1.0f));
}
