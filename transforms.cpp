#include "transforms.h"
#include "glm/gtx/transform.hpp"
#include <math.h>
#include <iostream>

Transforms::Transforms()
{

}

glm::mat4 Transforms::getScalingMatrix(float sx, float sy, float sz) {
    // Task 1: return the transformation matrix for 3D scaling
    // Task 4: modify the function to return a 4x4 matrix
    return glm::mat4(sx, 0.f, 0.f, 0.f,
                     0.f, sy, 0.f, 0.f,
                     0.f, 0.f, sz, 0.f,
                     0.f, 0.f, 0.f, 1.f);
}

glm::mat4 Transforms::getRotationMatrixX(float angle) {
    // Task 2: return the matrix for rotation about the x-axis
    // Task 4: modify the function to return a 4x4 matrix
    return glm::mat4(1.f, 0.f, 0.f, 0.f,
                     0.f, cos(angle * (M_PI / 180)), sin(angle * (M_PI / 180)), 0.f,
                     0.f, -sin(angle * (M_PI / 180)), cos(angle * (M_PI / 180)), 0.f,
                     0.f, 0.f, 0.f, 1.f);
}

glm::mat4 Transforms::getRotationMatrixY(float angle) {
    // Task 2: return the matrix for rotation about the y-axis
    // Task 4: modify the function to return a 4x4 matrix
    return glm::mat4(cos(angle * (M_PI / 180)), 0.f, -sin(angle * (M_PI / 180)), 0.f,
                     0.f, 1.f, 0.f, 0.f,
                     sin(angle * (M_PI / 180)), 0.f, cos(angle * (M_PI / 180)), 0.f,
                     0.f, 0.f, 0.f, 1.f);
}

glm::mat4 Transforms::getRotationMatrixZ(float angle) {
    // Task 2: return the matrix for rotation about the z-axis
    // Task 4: modify the function to return a 4x4 matrix
    return glm::mat4(cos(angle * (M_PI / 180)), sin(angle * (M_PI / 180)), 0.f, 0.f,
              -sin(angle * (M_PI / 180)), cos(angle * (M_PI / 180)), 0.f, 0.f,
              0.f, 0.f, 1.f, 0.f,
              0.f, 0.f, 0.f, 1.f);
}

glm::mat4 Transforms::getTranslationMatrix(float dx, float dy, float dz) {
    // Task 3: return the matrix for translation
    return glm::mat4(1.f, 0.f, 0.f, 0.f,
                     0.f, 1.f, 0.f, 0.f,
                     0.f, 0.f, 1.f, 0.f,
                     dx, dy, dz, 1.f);
}


glm::mat4 Transforms::getMatrixA() {
    // Task 5: return matrix A using the previous functions
    return getTranslationMatrix(0, -1, 0) * getScalingMatrix(2, -2, 1);
}

glm::mat4 Transforms::getMatrixB() {
    // Task 5: return matrix B using the previous functions
    return getRotationMatrixY(45);
}

glm::mat4 Transforms::getMatrixC() {
    // Task 5: return matrix C using the previous functions
    return getTranslationMatrix(4, 4, 0) * getRotationMatrixZ(30);
}

glm::mat4 Transforms::getMatrixD() {
    // Task 5: return matrix D using the previous functions
    return getTranslationMatrix(3, 1, 6) * getRotationMatrixX(30) * getScalingMatrix(0.5, 0.5, 0.5);
}


glm::mat4 Transforms::getViewMatrix(glm::vec3 pos, glm::vec3 look, glm::vec3 up) {
    // Task 7: return the camera view matrix
    glm::mat4 translate(1.f, 0.f, 0.f, 0.f,
                        0.f, 1.f, 0.f, 0.f,
                        0.f, 0.f, 1.f, 0.f,
                        -pos.x, -pos.y, -pos.z, 1.f);

    glm::vec3 w = -glm::normalize(look);
    glm::vec3 v = glm::normalize(up - glm::dot(up, w) * w);
    glm::vec3 u = glm::cross(v, w);

    glm::mat4 rotate(u.x, v.x, w.x, 0.f,
                     u.y, v.y, w.y, 0.f,
                     u.z, v.z, w.z, 0.f,
                     0.f, 0.f, 0.f, 1.f);

    return rotate * translate;
}
