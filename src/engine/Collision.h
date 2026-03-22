#pragma once

#include <glm/vec2.hpp>

namespace simple_engine {

struct AABB {
    glm::vec2 min;
    glm::vec2 max;

    AABB();
    AABB(const glm::vec2& minValue, const glm::vec2& maxValue);

    static AABB fromCenterAndHalfSize(const glm::vec2& center, const glm::vec2& halfSize);

    bool intersects(const AABB& other) const;
};

} // namespace simple_engine
