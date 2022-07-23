#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "glm.hpp"

class Transforms
{
public:
    Transforms();

    static glm::mat4 getObj1Matrix();
    static glm::mat4 getObj2Matrix();
    static glm::mat4 getObj3Matrix();

    static glm::mat4 getViewMatrix(glm::vec3 pos, glm::vec3 look, glm::vec3 up);

private:
    glm::mat3 getScalingMatrix(float sx, float sy, float sz);
    glm::mat3 getRotationMatrixX(float angle);
    glm::mat3 getRotationMatrixY(float angle);
    glm::mat3 getRotationMatrixZ(float angle);
    glm::mat4 getTranslationMatrix(float dx, float dy, float dz);

    glm::mat4 getMatrixA();
    glm::mat4 getMatrixB();
    glm::mat4 getMatrixC();
    glm::mat4 getMatrixD();
};

#endif // TRANSFORMS_H
