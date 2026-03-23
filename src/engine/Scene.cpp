#include "Scene.h"

#include <algorithm>
#include <memory>

#include "Material.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "Window.h"
#include "core/Logger.h"

namespace simple_engine {

Scene::Scene() {
    Logger::info("Scene created without GPU resources. Default shader will be created lazily.");
    m_lastViewportWidth = 1280;
    m_lastViewportHeight = 720;
}

void Scene::update(float deltaTime) {
    m_camera.update(deltaTime);

    for (const std::shared_ptr<ParallaxLayer>& layer : m_parallaxLayers) {
        if (!layer) {
            continue;
        }

        layer->update(m_camera.position);
    }

    for (const std::shared_ptr<RenderObject>& object : m_objects) {
        if (!object) {
            continue;
        }

        object->update(deltaTime);
    }

    bool tilemapChanged = false;
    for (const std::shared_ptr<Tilemap>& tilemap : m_tilemaps) {
        if (!tilemap) {
            continue;
        }

        for (const std::shared_ptr<Sprite>& sprite : tilemap->getSprites()) {
            if (!sprite) {
                continue;
            }

            sprite->update(deltaTime);
        }

        if (tilemap->isDirty()) {
            tilemap->clearDirty();
            tilemapChanged = true;
        }
    }

    if (tilemapChanged) {
        rebuildRenderObjects();
    }

    for (const std::shared_ptr<UIElement>& element : m_uiElements) {
        if (!element) {
            continue;
        }

        element->update(deltaTime);
    }
}

void Scene::render(Renderer& renderer, Window& window) {
    renderer.renderScene(window, *this);
}

RenderObject& Scene::createRenderObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& initialTransform, float initialRotationSpeed) {
    std::shared_ptr<RenderObject> object = std::make_shared<RenderObject>(std::move(mesh), std::move(material), initialTransform, initialRotationSpeed);
    m_objects.push_back(object);
    rebuildRenderObjects();
    return *object;
}

Sprite& Scene::createSprite(std::shared_ptr<Texture> texture, const Transform& initialTransform, const glm::vec4& tint, float initialRotationSpeed) {
    std::shared_ptr<Sprite> sprite = Sprite::create(ensureDefaultShader(), std::move(texture), initialTransform, tint);
    if (!sprite) {
        sprite = std::make_shared<Sprite>(Sprite::getSharedQuadMesh(), std::make_shared<Material>(), initialTransform);
    }

    sprite->rotationSpeed = initialRotationSpeed;
    m_objects.push_back(sprite);
    rebuildRenderObjects();
    return *sprite;
}

ParallaxLayer& Scene::addParallaxLayer(const ParallaxLayer& layer) {
    std::shared_ptr<ParallaxLayer> layerInstance = std::make_shared<ParallaxLayer>(layer);
    layerInstance->initialize(ensureDefaultShader());
    if (layerInstance->getSprite()) {
        layerInstance->update(m_camera.position);
    }
    m_parallaxLayers.push_back(layerInstance);
    rebuildRenderObjects();
    return *layerInstance;
}

UIElement& Scene::addUIElement(const UIElement& element) {
    std::shared_ptr<UIElement> elementInstance = std::make_shared<UIElement>(element);
    elementInstance->initialize(ensureDefaultShader());
    m_uiElements.push_back(elementInstance);
    rebuildUIRenderObjects();
    return *elementInstance;
}

bool Scene::moveObject(RenderObject& object, const glm::vec2& displacement, float collisionScale) {
    return moveObjectWithTileCollisions(object, displacement, collisionScale);
}

const std::vector<std::shared_ptr<RenderObject>>& Scene::getObjects() const {
    return m_renderObjects;
}

const std::vector<std::shared_ptr<RenderObject>>& Scene::getUIObjects() const {
    return m_uiRenderObjects;
}

const Camera& Scene::getCamera() const {
    return m_camera;
}

Camera& Scene::getCamera() {
    return m_camera;
}

std::shared_ptr<Shader> Scene::getDefaultShader() {
    return ensureDefaultShader();
}

int Scene::getLastViewportWidth() const {
    return m_lastViewportWidth;
}

int Scene::getLastViewportHeight() const {
    return m_lastViewportHeight;
}

Tilemap& Scene::addTilemap(const Tilemap& tilemap) {
    std::shared_ptr<Tilemap> tilemapInstance = std::make_shared<Tilemap>(tilemap);
    tilemapInstance->initialize(ensureDefaultShader());
    tilemapInstance->clearDirty();
    m_tilemaps.push_back(tilemapInstance);
    rebuildRenderObjects();
    return *tilemapInstance;
}

std::shared_ptr<Shader> Scene::ensureDefaultShader() {
    if (!m_defaultShader) {
        Logger::info("Creating default scene shader after OpenGL initialization.");
        m_defaultShader = Material::createDefaultShader();
    }

    return m_defaultShader;
}

void Scene::rebuildRenderObjects() {
    m_renderObjects.clear();

    for (const std::shared_ptr<ParallaxLayer>& layer : m_parallaxLayers) {
        if (!layer || !layer->getSprite()) {
            continue;
        }

        m_renderObjects.push_back(layer->getSprite());
    }

    for (const std::shared_ptr<RenderObject>& object : m_objects) {
        m_renderObjects.push_back(object);
    }

    for (const std::shared_ptr<Tilemap>& tilemap : m_tilemaps) {
        if (!tilemap) {
            continue;
        }

        for (const std::shared_ptr<Sprite>& sprite : tilemap->getSprites()) {
            m_renderObjects.push_back(sprite);
        }
    }

    std::stable_sort(m_renderObjects.begin(), m_renderObjects.end(), [](const std::shared_ptr<RenderObject>& left, const std::shared_ptr<RenderObject>& right) {
        if (!left || !right) {
            return static_cast<bool>(left);
        }

        return left->renderLayer < right->renderLayer;
    });
}

void Scene::rebuildUIRenderObjects() {
    m_uiRenderObjects.clear();

    for (const std::shared_ptr<UIElement>& element : m_uiElements) {
        if (!element || !element->getSprite()) {
            continue;
        }

        m_uiRenderObjects.push_back(element->getSprite());
    }

    std::stable_sort(m_uiRenderObjects.begin(), m_uiRenderObjects.end(), [](const std::shared_ptr<RenderObject>& left, const std::shared_ptr<RenderObject>& right) {
        if (!left || !right) {
            return static_cast<bool>(left);
        }

        return left->renderLayer < right->renderLayer;
    });
}

void Scene::updateUILayout(int viewportWidth, int viewportHeight) {
    m_lastViewportWidth = viewportWidth;
    m_lastViewportHeight = viewportHeight;

    for (const std::shared_ptr<UIElement>& element : m_uiElements) {
        if (!element) {
            continue;
        }

        element->updateLayout(viewportWidth, viewportHeight);
    }

    rebuildUIRenderObjects();
}

bool Scene::collidesWithSolidTiles(const AABB& bounds) const {
    for (const std::shared_ptr<Tilemap>& tilemap : m_tilemaps) {
        if (!tilemap) {
            continue;
        }

        if (tilemap->collidesWithAABB(bounds)) {
            return true;
        }
    }

    return false;
}

bool Scene::moveObjectWithTileCollisions(RenderObject& object, const glm::vec2& displacement, float collisionScale) {
    const glm::vec2 halfSize = getObjectHalfSize(object, collisionScale);
    glm::vec2 nextPosition = object.transform.position;
    bool moved = false;

    if (displacement.x != 0.0f) {
        const glm::vec2 candidate(nextPosition.x + displacement.x, nextPosition.y);
        if (!collidesWithSolidTiles(AABB::fromCenterAndHalfSize(candidate, halfSize))) {
            nextPosition.x = candidate.x;
            moved = true;
        }
    }

    if (displacement.y != 0.0f) {
        const glm::vec2 candidate(nextPosition.x, nextPosition.y + displacement.y);
        if (!collidesWithSolidTiles(AABB::fromCenterAndHalfSize(candidate, halfSize))) {
            nextPosition.y = candidate.y;
            moved = true;
        }
    }

    object.transform.position = nextPosition;
    return moved;
}

glm::vec2 Scene::getObjectHalfSize(const RenderObject& object, float collisionScale) const {
    return object.transform.scale * (0.5f * collisionScale);
}

} // namespace simple_engine
