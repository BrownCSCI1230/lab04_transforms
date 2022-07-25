#include "transforms.h"
#include "glm/gtx/transform.hpp"
#include <math.h>

Transforms::Transforms()
{

}

// TA SOLUTION: swap return type
// glm::mat4 Transforms::getScalingMatrix(float sx, float sy, float sz) {
glm::mat3 Transforms::getScalingMatrix(float sx, float sy, float sz) {
    // Task 1

    // TA SOLUTION
//    return glm::transpose(glm::mat4(sx, 0.f, 0.f, 0.f,
//                     0.f, sy, 0.f, 0.f,
//                     0.f, 0.f, sz, 0.f,
//                     0.f, 0.f, 0.f, 1.f));

    return glm::mat3();
}

// glm::mat4 Transforms::getRotationMatrixX(float angle) {
glm::mat3 Transforms::getRotationMatrixX(float angle) {
    // Task 2

    // TA SOLUTION
//    return glm::transpose(glm::mat4(1.f, 0.f, 0.f, 0.f,
//                     0.f, cos(angle * (M_PI / 180)), -sin(angle * (M_PI / 180)), 0.f,
//                     0.f, sin(angle * (M_PI / 180)), cos(angle * (M_PI / 180)), 0.f,
//                     0.f, 0.f, 0.f, 1.f));

    return glm::mat3();
}

//glm::mat4 Transforms::getRotationMatrixY(float angle) {
glm::mat3 Transforms::getRotationMatrixY(float angle) {
    // Task 2

    // TA SOLUTION
//    return glm::transpose(glm::mat4(cos(angle * (M_PI / 180)), 0.f, sin(angle * (M_PI / 180)), 0.f,
//                     0.f, 1.f, 0.f, 0.f,
//                     -sin(angle * (M_PI / 180)), 0.f, cos(angle * (M_PI / 180)), 0.f,
//                     0.f, 0.f, 0.f, 1.f));

    return glm::mat3();
}

//glm::mat4 Transforms::getRotationMatrixZ(float angle) {
glm::mat3 Transforms::getRotationMatrixZ(float angle) {
    // Task 2

    // TA SOLUTION
//    return glm::transpose(glm::mat4(cos(angle * (M_PI / 180)), -sin(angle * (M_PI / 180)), 0.f, 0.f,
//                     sin(angle * (M_PI / 180)), cos(angle * (M_PI / 180)), 0.f, 0.f,
//                     0.f, 0.f, 1.f, 0.f,
//                     0.f, 0.f, 0.f, 1.f));

    return glm::mat3();
}

glm::mat4 Transforms::getTranslationMatrix(float dx, float dy, float dz) {
    // Task 3

    // TA SOLUTION
//    return glm::transpose(glm::mat4(1.f, 0.f, 0.f, dx,
//                     0.f, 1.f, 0.f, dy,
//                     0.f, 0.f, 1.f, dz,
//                     0.f, 0.f, 0.f, 1.f));

    return glm::mat4();
}


glm::mat4 Transforms::getMatrixA() {
    // Task 5

    // TA SOLUTION
//    return getTranslationMatrix(0, -1, 0) * getScalingMatrix(2, -2, 1);

    return glm::mat4();
}

glm::mat4 Transforms::getMatrixB() {
    // Task 5

    // TA SOLUTION
//    return getRotationMatrixY(45);

    return glm::mat4();
}

glm::mat4 Transforms::getMatrixC() {
    // Task 5

    // TA SOLUTION
//    return getTranslationMatrix(4, 4, 0) * getRotationMatrixZ(30);

    return glm::mat4();
}

glm::mat4 Transforms::getMatrixD() {
    // Task 5

    // TA SOLUTION
//    return getTranslationMatrix(3, 1, 6) * getRotationMatrixX(30) * getScalingMatrix(0.5, 0.5, 0.5);

    return glm::mat4();
}


glm::mat4 Transforms::getObj1Matrix() {
    // Task 6

    // TA SOLUTION
//    return getMatrixC() * getMatrixA();

    return glm::mat4();
}

glm::mat4 Transforms::getObj2Matrix() {
    // Task 6

    // TA SOLUTION
//    return getMatrixC() * getMatrixB();

    return glm::mat4();
}

glm::mat4 Transforms::getObj3Matrix() {
    // Task 6

    // TA SOLUTION
//    return getMatrixD();

    return glm::mat4();
}


glm::mat4 Transforms::getViewMatrix(glm::vec3 pos, glm::vec3 look, glm::vec3 up) {
    // Task 7
    return glm::mat4();
}
