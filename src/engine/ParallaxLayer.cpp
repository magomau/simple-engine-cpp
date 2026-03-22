#include "ParallaxLayer.h"

#include <algorithm>
#include <memory>
#include <utility>

#include "Shader.h"
#include "Texture.h"

namespace simple_engine {

ParallaxLayer::ParallaxLayer()
    : m_region()
    , m_basePosition(0.0f, 0.0f)
    , m_size(1.0f, 1.0f)
    , m_tint(1.0f, 1.0f, 1.0f, 1.0f)
    , m_parallaxFactor(0.0f)
    , m_renderLayer(-100) {
}

ParallaxLayer::ParallaxLayer(std::shared_ptr<Texture> texture, const glm::vec2& basePosition, const glm::vec2& size, float parallaxFactor, const glm::vec4& tint, int renderLayer)
    : m_texture(std::move(texture))
    , m_region()
    , m_basePosition(basePosition)
    , m_size(size)
    , m_tint(tint)
    , m_parallaxFactor(parallaxFactor)
    , m_renderLayer(renderLayer) {
}

void ParallaxLayer::initialize(std::shared_ptr<Shader> shader) {
    if (!shader || !m_texture) {
        return;
    }

    Transform initialTransform;
    initialTransform.position = m_basePosition;
    initialTransform.scale = m_size;

    m_sprite = Sprite::create(std::move(shader), m_texture, initialTransform, m_tint);
    if (!m_sprite) {
        return;
    }

    m_sprite->renderLayer = m_renderLayer;
    m_sprite->setAtlasRegion(m_region);
}

void ParallaxLayer::update(const glm::vec2& cameraPosition) {
    if (!m_sprite) {
        return;
    }

    m_sprite->transform.position = m_basePosition + (cameraPosition * m_parallaxFactor);
}

void ParallaxLayer::setParallaxFactor(float parallaxFactor) {
    m_parallaxFactor = parallaxFactor;
}

float ParallaxLayer::getParallaxFactor() const {
    return m_parallaxFactor;
}

void ParallaxLayer::setBasePosition(const glm::vec2& basePosition) {
    m_basePosition = basePosition;
    if (m_sprite) {
        m_sprite->transform.position = m_basePosition;
    }
}

const glm::vec2& ParallaxLayer::getBasePosition() const {
    return m_basePosition;
}

void ParallaxLayer::setAtlasRegion(const AtlasRegion& region) {
    m_region = region.isValid() ? region : AtlasRegion();
    if (m_sprite) {
        m_sprite->setAtlasRegion(m_region);
    }
}

void ParallaxLayer::setRenderLayer(int renderLayer) {
    m_renderLayer = renderLayer;
    if (m_sprite) {
        m_sprite->renderLayer = m_renderLayer;
    }
}

int ParallaxLayer::getRenderLayer() const {
    return m_renderLayer;
}

std::shared_ptr<Sprite> ParallaxLayer::getSprite() const {
    return m_sprite;
}

} // namespace simple_engine
