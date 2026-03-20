#pragma once

#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

namespace simple_engine {

class RenderObject {
public:
    RenderObject();
    RenderObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& initialTransform, float initialRotationSpeed);

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    Transform transform;
    float rotationSpeed;
};

} // namespace simple_engine
