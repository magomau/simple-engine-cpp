#include "Sprite.h"

#include <memory>
#include <utility>

#include "Material.h"
#include "PrimitiveFactory.h"
#include "Shader.h"

namespace simple_engine {

Sprite::Sprite()
    : m_hasAnimation(false)
    , m_atlasRegion() {
}

Sprite::Sprite(std::shared_ptr<Mesh> sharedQuadMesh, std::shared_ptr<Material> spriteMaterial, const Transform& initialTransform)
    : RenderObject(std::move(sharedQuadMesh), std::move(spriteMaterial), initialTransform, 0.0f)
    , m_hasAnimation(false)
    , m_atlasRegion() {
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

void Sprite::update(float deltaTime) {
    RenderObject::update(deltaTime);

    if (!m_hasAnimation) {
        return;
    }

    std::shared_ptr<Material> spriteMaterial = getSpriteMaterial();
    if (!spriteMaterial) {
        return;
    }

    m_animation.update(deltaTime);
    m_animation.apply(*spriteMaterial);
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
    setAtlasRegion(AtlasRegion(minUV, maxUV));
}

void Sprite::setAtlasRegion(const AtlasRegion& region) {
    m_atlasRegion = region.isValid() ? region : AtlasRegion();

    if (m_hasAnimation) {
        setAnimationFromAtlasRegion(
            m_atlasRegion,
            m_animation.getFrameCount(),
            m_animation.getColumns(),
            m_animation.getRows(),
            m_animation.getFrameDuration(),
            m_animation.isLooping(),
            m_animation.getStartFrame());
        return;
    }

    applyCurrentTextureRegion();
}

void Sprite::setAtlasRegion(const TextureAtlas& atlas, int column, int row, int widthInCells, int heightInCells) {
    setTexture(atlas.getTexture());
    setAtlasRegion(atlas.getRegion(column, row, widthInCells, heightInCells));
}

void Sprite::setAtlasRegionByIndex(const TextureAtlas& atlas, int index, int widthInCells, int heightInCells) {
    setTexture(atlas.getTexture());
    setAtlasRegion(atlas.getRegionByIndex(index, widthInCells, heightInCells));
}

void Sprite::resetTextureRegion() {
    m_atlasRegion = AtlasRegion();
    applyCurrentTextureRegion();
}

void Sprite::setAnimationGrid(int frameCount, int columns, int rows, float frameDurationSeconds, bool shouldLoop, int startFrame) {
    setAnimationFromAtlasRegion(m_atlasRegion, frameCount, columns, rows, frameDurationSeconds, shouldLoop, startFrame);
}

void Sprite::setAnimationFromAtlasRegion(const AtlasRegion& region, int frameCount, int columns, int rows, float frameDurationSeconds, bool shouldLoop, int startFrame) {
    std::shared_ptr<Material> spriteMaterial = getSpriteMaterial();
    if (!spriteMaterial) {
        return;
    }

    m_atlasRegion = region.isValid() ? region : AtlasRegion();
    m_animation.configureGrid(frameCount, columns, rows, frameDurationSeconds, shouldLoop, startFrame, m_atlasRegion);
    m_animation.apply(*spriteMaterial);
    m_hasAnimation = m_animation.isValid();
}

void Sprite::clearAnimation() {
    m_hasAnimation = false;
    m_animation.stop();
    applyCurrentTextureRegion();
}

bool Sprite::hasAnimation() const {
    return m_hasAnimation;
}

SpriteAnimation& Sprite::getAnimation() {
    return m_animation;
}

const SpriteAnimation& Sprite::getAnimation() const {
    return m_animation;
}

const AtlasRegion& Sprite::getAtlasRegion() const {
    return m_atlasRegion;
}

std::shared_ptr<Material> Sprite::getSpriteMaterial() const {
    return material;
}

void Sprite::applyCurrentTextureRegion() {
    std::shared_ptr<Material> spriteMaterial = getSpriteMaterial();
    if (!spriteMaterial) {
        return;
    }

    if (m_hasAnimation) {
        m_animation.apply(*spriteMaterial);
        return;
    }

    spriteMaterial->setTextureRegion(m_atlasRegion.minUV, m_atlasRegion.maxUV);
}

} // namespace simple_engine
