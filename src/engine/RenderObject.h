#pragma once

#include <memory>

#include <glm/vec4.hpp>

#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

namespace simple_engine {

class RenderObject {
public:
    RenderObject();
    RenderObject(std::shared_ptr<Mesh> mesh, const Transform& initialTransform, float initialRotationSpeed, const glm::vec4& initialTintColor, std::shared_ptr<Texture> initialTexture = nullptr);

    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Texture> texture;
    Transform transform;
    float rotationSpeed;
    glm::vec4 tintColor;
};

} // namespace simple_engine
