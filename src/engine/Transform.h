#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>

namespace simple_engine {

class Transform {
public:
    Transform();

    glm::mat4 getMatrix() const;

    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
};

} // namespace simple_engine
