#include "GameObject.h"
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>

using tigl::Vertex;

float angle = 1.0f;
glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

GameObject::GameObject() {

}

void GameObject::drawCube() {
    angle += 0.0001f;

    glm::mat4 rotation(1.0f);
    rotation = glm::rotate(rotation, angle, glm::vec3(0, 0, 1.0f));
    tigl::shader->setViewMatrix(rotation);

    /*glm::vec4 color = glm::vec4(1, 0, 0, 1);
    glm::vec4 colorLeft = glm::vec4(0, 1, 0, 1);
    glm::vec4 colorRight = glm::vec4(0, 0, 1, 1);
    glm::vec4 colorFront = glm::vec4(1, 1, 0, 1);
    glm::vec4 colorUp = glm::vec4(0, 1, 1, 1);

    glm::vec4 bottomLeft = glm::vec4(0, 0, 0, 0);
    glm::vec4 bottomRight = glm::vec4(1, 0, 0, 0);
    glm::vec4 topLeft = glm::vec4(0, 1, 0, 0);
    glm::vec4 topRight = glm::vec4(1, 1, 0, 0);*/

    glm::vec4 bottomLeftFront = glm::vec4(-1, -1, -10, 1);// *camera->getInverseMatrix();
    glm::vec4 bottomLeftBack = glm::vec4(-1, -1, 0, 1);// *camera->getInverseMatrix();
    glm::vec4 bottomRightFront = glm::vec4(1, -1, -10, 1);// *camera->getInverseMatrix();
    glm::vec4 bottomRightBack = glm::vec4(1, -1, 0, 1);// *camera->getInverseMatrix();
    glm::vec4 topLeftFront = glm::vec4(-1, 1, -10, 1);// *camera->getInverseMatrix();
    glm::vec4 topLeftBack = glm::vec4(-1, 1, 0, 1);// *camera->getInverseMatrix();
    glm::vec4 topRightFront = glm::vec4(1, 1, -10, 1);// *camera->getInverseMatrix();
    glm::vec4 topRightBack = glm::vec4(1, 1, 0, 1);// *camera->getInverseMatrix();

    tigl::begin(GL_QUADS);
    tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, -5), color));
    tigl::addVertex(Vertex::PC(glm::vec3(1, 1, -5), color));
    tigl::addVertex(Vertex::PC(glm::vec3(1, 1, -5), color));
    tigl::addVertex(Vertex::PC(glm::vec3(1, -1, -5), color));
    tigl::addVertex(Vertex::PC(glm::vec3(1, -1, -5), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, -5), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-1, -1, -5), color));
    tigl::addVertex(Vertex::PC(glm::vec3(-1, 1, -5), color));

    tigl::end();
}

void GameObject::changeColor(glm::vec4 newColor) {
    color = newColor;
}