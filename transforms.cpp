#include "transforms.h"
#include "glm/gtx/transform.hpp"
#include <math.h>
#include <iostream>

Transforms::Transforms()
{

}

glm::mat3 Transforms::getScalingMatrix(float sx, float sy, float sz) {
    // Task 1: return the transformation matrix for 3D scaling
    // Task 4: modify the function to return a 4x4 matrix
    return glm::mat3();
}

glm::mat3 Transforms::getRotationMatrixX(float angle) {
    // Task 2: return the matrix for rotation about the x-axis
    // Task 4: modify the function to return a 4x4 matrix
    return glm::mat3();
}

glm::mat3 Transforms::getRotationMatrixY(float angle) {
    // Task 2: return the matrix for rotation about the y-axis
    // Task 4: modify the function to return a 4x4 matrix
    return glm::mat3();
}

glm::mat3 Transforms::getRotationMatrixZ(float angle) {
    // Task 2: return the matrix for rotation about the z-axis
    // Task 4: modify the function to return a 4x4 matrix
    return glm::mat3();
}

glm::mat4 Transforms::getTranslationMatrix(float dx, float dy, float dz) {
    // Task 3: return the matrix for translation
    return glm::mat4();
}


glm::mat4 Transforms::getMatrixA() {
    // Task 5: return matrix A using the previous functions
    return glm::mat4();
}

glm::mat4 Transforms::getMatrixB() {
    // Task 5: return matrix B using the previous functions
    return glm::mat4();
}

glm::mat4 Transforms::getMatrixC() {
    // Task 5: return matrix C using the previous functions
    return glm::mat4();
}

glm::mat4 Transforms::getMatrixD() {
    // Task 5: return matrix D using the previous functions
    return glm::mat4();
}


glm::mat4 Transforms::getViewMatrix(glm::vec3 pos, glm::vec3 look, glm::vec3 up) {
    // Task 7: return the camera view matrix
    return glm::mat4();
}
