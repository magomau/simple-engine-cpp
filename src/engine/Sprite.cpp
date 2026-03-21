#include "Sprite.h"

#include <memory>
#include <utility>

#include "Material.h"
#include "PrimitiveFactory.h"
#include "Shader.h"

namespace simple_engine {

Sprite::Sprite() = default;

Sprite::Sprite(std::shared_ptr<Mesh> sharedQuadMesh, std::shared_ptr<Material> spriteMaterial, const Transform& initialTransform)
    : RenderObject(std::move(sharedQuadMesh), std::move(spriteMaterial), initialTransform, 0.0f) {
}

std::shared_ptr<Sprite> Sprite::create(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture, const Transform& initialTransform, const glm::vec4& tint) {
    if (!shader) {
        return nullptr;
    }

    std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>(std::move(shader), tint, std::move(texture));
    return std::make_shared<Sprite>(getSharedQuadMesh(), spriteMaterial, initialTransform);
}

std::shared_ptr<Mesh> Sprite::getSharedQuadMesh() {
    static std::weak_ptr<Mesh> cachedQuadMesh;

    std::shared_ptr<Mesh> sharedQuadMesh = cachedQuadMesh.lock();
    if (!sharedQuadMesh) {
        sharedQuadMesh = PrimitiveFactory::createQuad();
        cachedQuadMesh = sharedQuadMesh;
    }

    return sharedQuadMesh;
}

void Sprite::setTexture(std::shared_ptr<Texture> texture) {
    std::shared_ptr<Material> spriteMaterial = getSpriteMaterial();
    if (!spriteMaterial) {
        return;
    }

    spriteMaterial->texture = std::move(texture);
}

void Sprite::setTint(const glm::vec4& tint) {
    std::shared_ptr<Material> spriteMaterial = getSpriteMaterial();
    if (!spriteMaterial) {
        return;
    }

    spriteMaterial->baseColor = tint;
}

void Sprite::setSize(const glm::vec2& size) {
    transform.scale = size;
}

void Sprite::setTextureRegion(const glm::vec2& minUV, const glm::vec2& maxUV) {
    std::shared_ptr<Material> spriteMaterial = getSpriteMaterial();
    if (!spriteMaterial) {
        return;
    }

    spriteMaterial->setTextureRegion(minUV, maxUV);
}

void Sprite::resetTextureRegion() {
    std::shared_ptr<Material> spriteMaterial = getSpriteMaterial();
    if (!spriteMaterial) {
        return;
    }

    spriteMaterial->resetTextureRegion();
}

std::shared_ptr<Material> Sprite::getSpriteMaterial() const {
    return material;
}

} // namespace simple_engine
