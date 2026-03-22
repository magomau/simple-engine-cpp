#include "Scene.h"

#include <memory>
#include <string>

#include <glm/geometric.hpp>
#include <glm/vec4.hpp>

#include "Material.h"
#include "PrimitiveFactory.h"
#include "Renderer.h"
#include "Sprite.h"
#include "Tilemap.h"
#include "Texture.h"
#include "Window.h"

namespace simple_engine {

Scene::Scene()
    : m_cameraInputDirection(0.0f, 0.0f)
    , m_cameraMoveSpeed(1.8f)
    , m_cameraFollowOffset(0.0f, 0.0f) {
    const std::shared_ptr<Mesh> triangleMesh = PrimitiveFactory::createTriangle();
    m_defaultShader = Material::createDefaultShader();

    std::shared_ptr<Texture> checkerTexture = std::make_shared<Texture>();
    const std::string texturePath = std::string(SIMPLE_ENGINE_ASSET_ROOT) + "/checker.ppm";
    if (!checkerTexture->loadFromFile(texturePath)) {
        checkerTexture.reset();
    }

    const std::shared_ptr<Material> orangeMaterial = std::make_shared<Material>(m_defaultShader, glm::vec4(0.95f, 0.55f, 0.20f, 1.0f));
    const std::shared_ptr<Material> blueMaterial = std::make_shared<Material>(m_defaultShader, glm::vec4(0.35f, 0.85f, 1.0f, 1.0f));
    const std::shared_ptr<Material> greenMaterial = std::make_shared<Material>(m_defaultShader, glm::vec4(0.45f, 1.0f, 0.55f, 1.0f));

    Transform playerTransform;
    playerTransform.position = { 0.0f, 1.5f };
    playerTransform.scale = { 1.0f, 1.0f };
    createRenderObject(triangleMesh, orangeMaterial, playerTransform, 1.0f);

    Transform leftTransform;
    leftTransform.position = { -0.9f, 0.45f };
    leftTransform.scale = { 0.65f, 0.65f };
    createRenderObject(triangleMesh, blueMaterial, leftTransform, -0.7f);

    Transform spriteTransform;
    spriteTransform.position = { 0.95f, -0.35f };
    spriteTransform.scale = { 0.85f, 1.1f };
    createSprite(checkerTexture, spriteTransform, glm::vec4(1.0f), 0.45f);

    Transform topTransform;
    topTransform.position = { 0.35f, 0.8f };
    topTransform.scale = { 0.55f, 0.55f };
    createRenderObject(Sprite::getSharedQuadMesh(), greenMaterial, topTransform, -0.3f);

    TextureAtlas tileAtlas(checkerTexture, 2, 2);
    Tilemap collisionTilemap(tileAtlas, 8, 6, glm::vec2(0.5f, 0.5f), glm::vec2(-2.0f, 2.0f));

    for (int x = 0; x < collisionTilemap.getWidth(); ++x) {
        collisionTilemap.setTile(x, collisionTilemap.getHeight() - 1, x % 4);
        collisionTilemap.setTileSolid(x, collisionTilemap.getHeight() - 1, true);
    }

    for (int y = 2; y < collisionTilemap.getHeight(); ++y) {
        collisionTilemap.setTile(0, y, 1);
        collisionTilemap.setTileSolid(0, y, true);
    }

    collisionTilemap.setTile(3, 4, 2);
    collisionTilemap.setTileSolid(3, 4, true);
    collisionTilemap.setTile(4, 4, 3);
    collisionTilemap.setTileSolid(4, 4, true);
    collisionTilemap.setTile(5, 3, 0);
    collisionTilemap.setTileSolid(5, 3, true);

    addTilemap(collisionTilemap);
}

void Scene::update(float deltaTime) {
    if (glm::length(m_cameraInputDirection) > 0.0f) {
        const glm::vec2 direction = glm::normalize(m_cameraInputDirection);
        m_cameraFollowOffset += direction * (m_cameraMoveSpeed * deltaTime);
    }

    RenderObject* primaryObject = getPrimaryObject();
    if (primaryObject != nullptr) {
        m_camera.setFollowTarget(primaryObject->transform.position + m_cameraFollowOffset);
    } else {
        m_camera.clearFollowTarget();
    }

    m_camera.update(deltaTime);

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
}

void Scene::render(Renderer& renderer, Window& window) const {
    renderer.renderScene(window, *this);
}

RenderObject& Scene::createRenderObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material, const Transform& initialTransform, float initialRotationSpeed) {
    std::shared_ptr<RenderObject> object = std::make_shared<RenderObject>(std::move(mesh), std::move(material), initialTransform, initialRotationSpeed);
    m_objects.push_back(object);
    rebuildRenderObjects();
    return *object;
}

Sprite& Scene::createSprite(std::shared_ptr<Texture> texture, const Transform& initialTransform, const glm::vec4& tint, float initialRotationSpeed) {
    if (!m_defaultShader) {
        m_defaultShader = Material::createDefaultShader();
    }

    std::shared_ptr<Sprite> sprite = Sprite::create(m_defaultShader, std::move(texture), initialTransform, tint);
    if (!sprite) {
        sprite = std::make_shared<Sprite>(Sprite::getSharedQuadMesh(), std::make_shared<Material>(), initialTransform);
    }

    sprite->rotationSpeed = initialRotationSpeed;
    m_objects.push_back(sprite);
    rebuildRenderObjects();
    return *sprite;
}

bool Scene::movePrimaryObject(const glm::vec2& displacement, float collisionScale) {
    RenderObject* primaryObject = getPrimaryObject();
    if (primaryObject == nullptr) {
        return false;
    }

    return moveObjectWithTileCollisions(*primaryObject, displacement, collisionScale);
}

const std::vector<std::shared_ptr<RenderObject>>& Scene::getObjects() const {
    return m_renderObjects;
}

RenderObject* Scene::getPrimaryObject() {
    if (m_objects.empty()) {
        return nullptr;
    }

    return m_objects.front().get();
}

const Camera& Scene::getCamera() const {
    return m_camera;
}

Camera& Scene::getCamera() {
    return m_camera;
}

void Scene::setCameraInputDirection(const glm::vec2& direction) {
    m_cameraInputDirection = direction;
}

Tilemap& Scene::addTilemap(const Tilemap& tilemap) {
    std::shared_ptr<Tilemap> tilemapInstance = std::make_shared<Tilemap>(tilemap);
    tilemapInstance->initialize(m_defaultShader);
    tilemapInstance->clearDirty();
    m_tilemaps.push_back(tilemapInstance);
    rebuildRenderObjects();
    return *tilemapInstance;
}

void Scene::rebuildRenderObjects() {
    m_renderObjects = m_objects;

    for (const std::shared_ptr<Tilemap>& tilemap : m_tilemaps) {
        if (!tilemap) {
            continue;
        }

        for (const std::shared_ptr<Sprite>& sprite : tilemap->getSprites()) {
            m_renderObjects.push_back(sprite);
        }
    }
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
