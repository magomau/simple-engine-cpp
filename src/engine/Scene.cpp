#include "Scene.h"

#include <memory>

#include "PrimitiveFactory.h"

namespace simple_engine {

Scene::Scene() {
    const std::shared_ptr<Mesh> triangleMesh = PrimitiveFactory::createTriangle();
    const std::shared_ptr<Mesh> quadMesh = PrimitiveFactory::createQuad();

    Transform playerTransform;
    playerTransform.position = { 0.0f, 0.0f };
    playerTransform.scale = { 1.0f, 1.0f };
    m_objects.emplace_back(triangleMesh, playerTransform, 1.0f);

    Transform leftTransform;
    leftTransform.position = { -0.9f, 0.45f };
    leftTransform.scale = { 0.65f, 0.65f };
    m_objects.emplace_back(triangleMesh, leftTransform, -0.7f);

    Transform rightTransform;
    rightTransform.position = { 0.95f, -0.35f };
    rightTransform.scale = { 0.85f, 1.1f };
    m_objects.emplace_back(quadMesh, rightTransform, 0.45f);

    Transform topTransform;
    topTransform.position = { 0.35f, 0.8f };
    topTransform.scale = { 0.55f, 0.55f };
    m_objects.emplace_back(quadMesh, topTransform, -0.3f);
}

void Scene::update(float deltaTime) {
    for (RenderObject& object : m_objects) {
        object.transform.rotation += object.rotationSpeed * deltaTime;
    }
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

} // namespace simple_engine
