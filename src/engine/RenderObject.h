#pragma once

#include <memory>

#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

namespace simple_engine {

class RenderObject {
public:
    RenderObject();
    RenderObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& initialTransform, float initialRotationSpeed, int initialRenderLayer = 0);
    virtual ~RenderObject() = default;

    virtual void update(float deltaTime);

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
    Transform transform;
    float rotationSpeed;
    int renderLayer;
};

} // namespace simple_engine
