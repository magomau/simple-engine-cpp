#pragma once

#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Sprite.h"
#include "TextureAtlas.h"

namespace simple_engine {

class Shader;
class Texture;

class ParallaxLayer {
public:
    ParallaxLayer();
    ParallaxLayer(std::shared_ptr<Texture> texture, const glm::vec2& basePosition, const glm::vec2& size, float parallaxFactor, const glm::vec4& tint = glm::vec4(1.0f), int renderLayer = -100);

    void initialize(std::shared_ptr<Shader> shader);
    void update(const glm::vec2& cameraPosition);

    void setParallaxFactor(float parallaxFactor);
    float getParallaxFactor() const;
    void setBasePosition(const glm::vec2& basePosition);
    const glm::vec2& getBasePosition() const;
    void setAtlasRegion(const AtlasRegion& region);
    void setRenderLayer(int renderLayer);
    int getRenderLayer() const;
    std::shared_ptr<Sprite> getSprite() const;

private:
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Sprite> m_sprite;
    AtlasRegion m_region;
    glm::vec2 m_basePosition;
    glm::vec2 m_size;
    glm::vec4 m_tint;
    float m_parallaxFactor;
    int m_renderLayer;
};

} // namespace simple_engine
