#pragma once

#include <glm/vec2.hpp>

#include "Input.h"

namespace simple_engine {

class Application {
public:
    Application();

    void processEvents(bool& running);
    void update(float deltaTime);

    const glm::vec2& getTrianglePosition() const;

private:
    Input m_input;
    glm::vec2 m_trianglePosition;
    float m_moveSpeed;
};

} // namespace simple_engine
