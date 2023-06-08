#include "ComputerController.h"

ComputerController::ComputerController(bool newIsDrawing) {
	setIsDrawing(newIsDrawing);
}

void ComputerController::setIsDrawing(bool newIsDrawing) {
	isDrawing = newIsDrawing;
}

void ComputerController::handleDraw(const glm::vec3& position, const glm::mat4& rotation) {
	if (isDrawing) {
		for (const auto& object : objects)
		{
			object.Draw(position, rotation);
		}
	}
}
