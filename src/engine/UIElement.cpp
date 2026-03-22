#include "UIElement.h"

#include <memory>
#include <utility>

#include "Shader.h"
#include "Texture.h"

namespace simple_engine {

UIElement::UIElement()
    : m_region()
    , m_screenPosition(0.0f, 0.0f)
    , m_size(32.0f, 32.0f)
    , m_tint(1.0f, 1.0f, 1.0f, 1.0f)
    , m_anchor(UIAnchor::TopLeft)
    , m_renderLayer(1000) {
}

UIElement::UIElement(std::shared_ptr<Texture> texture, const glm::vec2& screenPosition, const glm::vec2& size, UIAnchor anchor, const glm::vec4& tint, int renderLayer)
    : m_texture(std::move(texture))
    , m_region()
    , m_screenPosition(screenPosition)
    , m_size(size)
    , m_tint(tint)
    , m_anchor(anchor)
    , m_renderLayer(renderLayer) {
}

void UIElement::initialize(std::shared_ptr<Shader> shader) {
    if (!shader || !m_texture) {
        return;
    }

    Transform initialTransform;
    initialTransform.scale = m_size;

    m_sprite = Sprite::create(std::move(shader), m_texture, initialTransform, m_tint);
    if (!m_sprite) {
        return;
    }

    m_sprite->renderLayer = m_renderLayer;
    m_sprite->setAtlasRegion(m_region);
}

void UIElement::update(float deltaTime) {
    if (!m_sprite) {
        return;
    }

    m_sprite->update(deltaTime);
}

void UIElement::updateLayout(int viewportWidth, int viewportHeight) {
    if (!m_sprite) {
        return;
    }

    m_sprite->transform.scale = m_size;
    m_sprite->transform.position = getAnchoredPosition(viewportWidth, viewportHeight);
    m_sprite->renderLayer = m_renderLayer;
}

void UIElement::setScreenPosition(const glm::vec2& screenPosition) {
    m_screenPosition = screenPosition;
}

void UIElement::setSize(const glm::vec2& size) {
    m_size = size;
}

void UIElement::setAnchor(UIAnchor anchor) {
    m_anchor = anchor;
}

void UIElement::setRenderLayer(int renderLayer) {
    m_renderLayer = renderLayer;
    if (m_sprite) {
        m_sprite->renderLayer = m_renderLayer;
    }
}

void UIElement::setAtlasRegion(const AtlasRegion& region) {
    m_region = region.isValid() ? region : AtlasRegion();
    if (m_sprite) {
        m_sprite->setAtlasRegion(m_region);
    }
}

const glm::vec2& UIElement::getScreenPosition() const {
    return m_screenPosition;
}

const glm::vec2& UIElement::getSize() const {
    return m_size;
}

UIAnchor UIElement::getAnchor() const {
    return m_anchor;
}

int UIElement::getRenderLayer() const {
    return m_renderLayer;
}

std::shared_ptr<Sprite> UIElement::getSprite() const {
    return m_sprite;
}

glm::vec2 UIElement::getAnchoredPosition(int viewportWidth, int viewportHeight) const {
    const glm::vec2 halfSize = m_size * 0.5f;

    switch (m_anchor) {
    case UIAnchor::TopLeft:
        return glm::vec2(m_screenPosition.x + halfSize.x, static_cast<float>(viewportHeight) - m_screenPosition.y - halfSize.y);
    case UIAnchor::TopRight:
        return glm::vec2(static_cast<float>(viewportWidth) - m_screenPosition.x - halfSize.x, static_cast<float>(viewportHeight) - m_screenPosition.y - halfSize.y);
    case UIAnchor::BottomLeft:
        return glm::vec2(m_screenPosition.x + halfSize.x, m_screenPosition.y + halfSize.y);
    case UIAnchor::BottomRight:
        return glm::vec2(static_cast<float>(viewportWidth) - m_screenPosition.x - halfSize.x, m_screenPosition.y + halfSize.y);
    case UIAnchor::Center:
    default:
        return glm::vec2((static_cast<float>(viewportWidth) * 0.5f) + m_screenPosition.x, (static_cast<float>(viewportHeight) * 0.5f) + m_screenPosition.y);
    }
}

} // namespace simple_engine
