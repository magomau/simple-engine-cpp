#pragma once

#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "RenderObject.h"

namespace simple_engine {

class Shader;
class Texture;

class Sprite : public RenderObject {
public:
    Sprite();
    Sprite(std::shared_ptr<Mesh> sharedQuadMesh, std::shared_ptr<Material> spriteMaterial, const Transform& initialTransform = Transform());

    static std::shared_ptr<Sprite> create(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, const Transform& initialTransform = Transform(), const glm::vec4& tint = glm::vec4(1.0f));
    static std::shared_ptr<Mesh> getSharedQuadMesh();

    void setTexture(std::shared_ptr<Texture> texture);
    void setTint(const glm::vec4& tint);
    void setSize(const glm::vec2& size);
    void setTextureRegion(const glm::vec2& minUV, const glm::vec2& maxUV);
    void resetTextureRegion();

private:
    std::shared_ptr<Material> getSpriteMaterial() const;
};

} // namespace simple_engine
