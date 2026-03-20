#include "Scene.h"

#include <memory>
#include <string>

#include <glm/geometric.hpp>
#include <glm/vec4.hpp>

#include "PrimitiveFactory.h"
#include "Renderer.h"
#include "Texture.h"
#include "Window.h"

namespace simple_engine {

Scene::Scene()
    : m_objectInputDirection(0.0f, 0.0f)
    , m_cameraInputDirection(0.0f, 0.0f)
    , m_objectMoveSpeed(1.5f)
    , m_cameraMoveSpeed(1.8f) {
    const std::shared_ptr<Mesh> triangleMesh = PrimitiveFactory::createTriangle();
    const std::shared_ptr<Mesh> quadMesh = PrimitiveFactory::createQuad();

    std::shared_ptr<Texture> checkerTexture = std::make_shared<Texture>();
    const std::string texturePath = std::string(SIMPLE_ENGINE_ASSET_ROOT) + "/checker.ppm";
    if (!checkerTexture->loadFromFile(texturePath)) {
        checkerTexture.reset();
    }

    Transform playerTransform;
    playerTransform.position = { 0.0f, 0.0f };
    playerTransform.scale = { 1.0f, 1.0f };
    m_objects.emplace_back(triangleMesh, playerTransform, 1.0f, glm::vec4(0.95f, 0.55f, 0.20f, 1.0f));

    Transform leftTransform;
    leftTransform.position = { -0.9f, 0.45f };
    leftTransform.scale = { 0.65f, 0.65f };
    m_objects.emplace_back(triangleMesh, leftTransform, -0.7f, glm::vec4(0.35f, 0.85f, 1.0f, 1.0f));

    Transform rightTransform;
    rightTransform.position = { 0.95f, -0.35f };
    rightTransform.scale = { 0.85f, 1.1f };
    m_objects.emplace_back(quadMesh, rightTransform, 0.45f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), checkerTexture);

    Transform topTransform;
    topTransform.position = { 0.35f, 0.8f };
    topTransform.scale = { 0.55f, 0.55f };
    m_objects.emplace_back(quadMesh, topTransform, -0.3f, glm::vec4(0.45f, 1.0f, 0.55f, 1.0f));
}

void Scene::update(float deltaTime) {
    if (glm::length(m_objectInputDirection) > 0.0f) {
        const glm::vec2 direction = glm::normalize(m_objectInputDirection);
        RenderObject* playerObject = getPrimaryObject();
        if (playerObject != nullptr) {
            playerObject->transform.position += direction * (m_objectMoveSpeed * deltaTime);
        }
    }

    if (glm::length(m_cameraInputDirection) > 0.0f) {
        const glm::vec2 direction = glm::normalize(m_cameraInputDirection);
        m_camera.position += direction * (m_cameraMoveSpeed * deltaTime);
    }

    for (RenderObject& object : m_objects) {
        object.transform.rotation += object.rotationSpeed * deltaTime;
    }
}

void Scene::render(Renderer& renderer, Window& window) const {
    renderer.renderScene(window, *this);
}

const std::vector<RenderObject>& Scene::getObjects() const {
    return m_objects;
}

RenderObject* Scene::getPrimaryObject() {
    if (m_objects.empty()) {
        return nullptr;
    }

    return &m_objects.front();
}

const Camera& Scene::getCamera() const {
    return m_camera;
}

Camera& Scene::getCamera() {
    return m_camera;
}

void Scene::setObjectInputDirection(const glm::vec2& direction) {
    m_objectInputDirection = direction;
}

void Scene::setCameraInputDirection(const glm::vec2& direction) {
    m_cameraInputDirection = direction;
}

} // namespace simple_engine
