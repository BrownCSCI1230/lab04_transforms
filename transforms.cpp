#include "transforms.h"
#include "glm/gtx/transform.hpp"

Transforms::Transforms()
{

}


glm::mat3 Transforms::getScalingMatrix(float sx, float sy, float sz) {
    // Task 1
    return glm::mat3();
}

glm::mat3 Transforms::getRotationMatrixX(float angle) {
    // Task 2
    return glm::mat3();
}

glm::mat3 Transforms::getRotationMatrixY(float angle) {
    // Task 2
    return glm::mat3();
}

glm::mat3 Transforms::getRotationMatrixZ(float angle) {
    // Task 2
    return glm::mat3();
}

glm::mat4 Transforms::getTranslationMatrix(float dx, float dy, float dz) {
    // Task 3
    return glm::mat4();
}


glm::mat4 Transforms::getMatrixA() {
    // Task 5
    return glm::mat4();
}

glm::mat4 Transforms::getMatrixB() {
    // Task 5
    return glm::mat4();
}

glm::mat4 Transforms::getMatrixC() {
    // Task 5
    return glm::mat4();
}

glm::mat4 Transforms::getMatrixD() {
    // Task 5
    return glm::mat4();
}


glm::mat4 Transforms::getObj1Matrix() {
    // Task 6
    return glm::scale(glm::vec3(2, 2, 2));
    return glm::mat4();
}

glm::mat4 Transforms::getObj2Matrix() {
    // Task 6
    return glm::rotate(45.f, glm::vec3(0, 0, 1));
    return glm::mat4();
}

glm::mat4 Transforms::getObj3Matrix() {
    // Task 6
    return glm::translate(glm::vec3(1, 2, 3));
    return glm::mat4();
}


glm::mat4 Transforms::getViewMatrix(glm::vec3 pos, glm::vec3 look, glm::vec3 up) {
    // Task 7
    return glm::mat4();
}
