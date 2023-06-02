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
	if (isDrawing) {
		drawCurrentObject();
	}
}

void ComputerController::setCurrentObject(GameObject currentObject) {
	ComputerController::currentObject = currentObject;
}

void ComputerController::drawCurrentObject() {
	ComputerController::currentObject.drawCube();
}
