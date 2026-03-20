#pragma once

#include <memory>

#include "Mesh.h"
#include "Transform.h"

namespace simple_engine {

class RenderObject {
public:
    RenderObject();
    RenderObject(std::shared_ptr<Mesh> mesh, const Transform& initialTransform, float initialRotationSpeed);

    std::shared_ptr<Mesh> mesh;
    Transform transform;
    float rotationSpeed;
};

} // namespace simple_engine
