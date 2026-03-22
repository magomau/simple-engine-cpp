#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Camera.h"
#include "Collision.h"
#include "Material.h"
#include "ParallaxLayer.h"
#include "RenderObject.h"
#include "UIElement.h"

namespace simple_engine {

class Renderer;
class Shader;
class ParallaxLayer;
class Sprite;
class Texture;
class Tilemap;
class UIElement;
class Window;

class Scene {
public:
    Scene();
    virtual ~Scene() = default;

    virtual void update(float deltaTime);
    void render(Renderer& renderer, Window& window);

    RenderObject& createRenderObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& initialTransform, float initialRotationSpeed = 0.0f);
    Sprite& createSprite(std::shared_ptr<Texture> texture, const Transform& initialTransform, const glm::vec4& tint = glm::vec4(1.0f), float initialRotationSpeed = 0.0f);
    Tilemap& addTilemap(const Tilemap& tilemap);
    ParallaxLayer& addParallaxLayer(const ParallaxLayer& layer);
    UIElement& addUIElement(const UIElement& element);
    bool moveObject(RenderObject& object, const glm::vec2& displacement, float collisionScale = 0.8f);
    void updateUILayout(int viewportWidth, int viewportHeight);

    const std::vector<std::shared_ptr<RenderObject>>& getObjects() const;
    const std::vector<std::shared_ptr<RenderObject>>& getUIObjects() const;
    const Camera& getCamera() const;
    Camera& getCamera();
    std::shared_ptr<Shader> getDefaultShader();

private:
    std::shared_ptr<Shader> ensureDefaultShader();
    bool moveObjectWithTileCollisions(RenderObject& object, const glm::vec2& displacement, float collisionScale);
    bool collidesWithSolidTiles(const AABB& bounds) const;
    glm::vec2 getObjectHalfSize(const RenderObject& object, float collisionScale) const;
    void rebuildRenderObjects();
    void rebuildUIRenderObjects();

    std::vector<std::shared_ptr<RenderObject>> m_objects;
    std::vector<std::shared_ptr<ParallaxLayer>> m_parallaxLayers;
    std::vector<std::shared_ptr<Tilemap>> m_tilemaps;
    std::vector<std::shared_ptr<RenderObject>> m_renderObjects;
    std::vector<std::shared_ptr<UIElement>> m_uiElements;
    std::vector<std::shared_ptr<RenderObject>> m_uiRenderObjects;
    std::shared_ptr<Shader> m_defaultShader;
    Camera m_camera;
};

} // namespace simple_engine
