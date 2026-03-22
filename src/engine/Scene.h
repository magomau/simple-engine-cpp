#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Camera.h"
#include "Material.h"
#include "RenderObject.h"

namespace simple_engine {

class Renderer;
class Shader;
class Sprite;
class Texture;
class Tilemap;
class Window;

class Scene {
public:
    Scene();

    void update(float deltaTime);
    void render(Renderer& renderer, Window& window) const;

    RenderObject& createRenderObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& initialTransform, float initialRotationSpeed = 0.0f);
    Sprite& createSprite(std::shared_ptr<Texture> texture, const Transform& initialTransform, const glm::vec4& tint = glm::vec4(1.0f), float initialRotationSpeed = 0.0f);
    Tilemap& addTilemap(const Tilemap& tilemap);

    const std::vector<std::shared_ptr<RenderObject>>& getObjects() const;
    RenderObject* getPrimaryObject();
    const Camera& getCamera() const;
    Camera& getCamera();
    void setObjectInputDirection(const glm::vec2& direction);
    void setCameraInputDirection(const glm::vec2& direction);

private:
    void rebuildRenderObjects();

    std::vector<std::shared_ptr<RenderObject>> m_objects;
    std::vector<std::shared_ptr<Tilemap>> m_tilemaps;
    std::vector<std::shared_ptr<RenderObject>> m_renderObjects;
    std::shared_ptr<Shader> m_defaultShader;
    Camera m_camera;
    glm::vec2 m_objectInputDirection;
    glm::vec2 m_cameraInputDirection;
    float m_objectMoveSpeed;
    float m_cameraMoveSpeed;
};

} // namespace simple_engine
