#pragma once

#include "Transform.h"

namespace simple_engine {

class RenderObject {
public:
    RenderObject();
    RenderObject(const Transform& initialTransform, float initialRotationSpeed);

    Transform transform;
    float rotationSpeed;
};

} // namespace simple_engine
