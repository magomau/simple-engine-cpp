#include "Collision.h"

namespace simple_engine {

AABB::AABB()
    : min(0.0f, 0.0f)
    , max(0.0f, 0.0f) {
}

AABB::AABB(const glm::vec2& minValue, const glm::vec2& maxValue)
    : min(minValue)
    , max(maxValue) {
}

AABB AABB::fromCenterAndHalfSize(const glm::vec2& center, const glm::vec2& halfSize) {
    return AABB(center - halfSize, center + halfSize);
}

bool AABB::intersects(const AABB& other) const {
    return min.x < other.max.x && max.x > other.min.x
        && min.y < other.max.y && max.y > other.min.y;
}

} // namespace simple_engine
