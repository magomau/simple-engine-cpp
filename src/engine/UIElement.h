#pragma once

#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Sprite.h"
#include "TextureAtlas.h"

namespace simple_engine {

class Shader;
class Texture;

enum class UIAnchor {
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    Center,
};

class UIElement {
public:
    UIElement();
    UIElement(std::shared_ptr<Texture> texture, const glm::vec2& screenPosition, const glm::vec2& size, UIAnchor anchor = UIAnchor::TopLeft, const glm::vec4& tint = glm::vec4(1.0f), int renderLayer = 1000);

    void initialize(std::shared_ptr<Shader> shader);
    void update(float deltaTime);
    void updateLayout(int viewportWidth, int viewportHeight);

    void setScreenPosition(const glm::vec2& screenPosition);
    void setSize(const glm::vec2& size);
    void setAnchor(UIAnchor anchor);
    void setRenderLayer(int renderLayer);
    void setTint(const glm::vec4& tint);
    void setAtlasRegion(const AtlasRegion& region);

    const glm::vec2& getScreenPosition() const;
    const glm::vec2& getSize() const;
    UIAnchor getAnchor() const;
    int getRenderLayer() const;
    const glm::vec4& getTint() const;
    std::shared_ptr<Sprite> getSprite() const;
    bool containsScreenPoint(const glm::vec2& screenPoint, int viewportWidth, int viewportHeight) const;

private:
    glm::vec2 getAnchoredPosition(int viewportWidth, int viewportHeight) const;

    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Sprite> m_sprite;
    AtlasRegion m_region;
    glm::vec2 m_screenPosition;
    glm::vec2 m_size;
    glm::vec4 m_tint;
    UIAnchor m_anchor;
    int m_renderLayer;
};

} // namespace simple_engine
