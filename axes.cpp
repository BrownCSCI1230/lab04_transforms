#include "axes.h"

Axes::Axes() {

}

Axes::Axes(glm::mat4 model, glm::vec3 color)
{
    m_model = model;
    m_color = color;
}

void Axes::applyTransform(glm::mat4 transform) {
    m_model = transform;
    // TODO: update
}

void Axes::draw() {
    // TODO: draw axes
}
