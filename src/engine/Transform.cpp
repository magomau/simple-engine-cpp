#include "Transform.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/vec3.hpp>

namespace simple_engine {

Transform::Transform()
    : position(0.0f, 0.0f)
    , rotation(0.0f)
    , scale(1.0f, 1.0f) {
}

glm::mat4 Transform::getMatrix() const {
    const glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
    const glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
    return translation * rotationMatrix * scaleMatrix;
}

} // namespace simple_engine
