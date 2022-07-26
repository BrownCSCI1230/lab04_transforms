#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "glm.hpp"

class Transforms
{
public:
    Transforms();

    static glm::mat4 getMatrixA();
    static glm::mat4 getMatrixB();
    static glm::mat4 getMatrixC();
    static glm::mat4 getMatrixD();

    static glm::mat4 getViewMatrix(glm::vec3 pos, glm::vec3 look, glm::vec3 up);

private:
    // Task 4: modify function headers to return a 4x4 matrix
    static glm::mat4 getScalingMatrix(float sx, float sy, float sz);
    static glm::mat4 getRotationMatrixX(float angle);
    static glm::mat4 getRotationMatrixY(float angle);
    static glm::mat4 getRotationMatrixZ(float angle);

    static glm::mat4 getTranslationMatrix(float dx, float dy, float dz);
};

#endif // TRANSFORMS_H
