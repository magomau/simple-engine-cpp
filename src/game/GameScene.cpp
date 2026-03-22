#include "GameScene.h"

#include <memory>
#include <string>

#include <glm/vec4.hpp>

#include "engine/Collision.h"
#include "engine/Material.h"
#include "engine/ParallaxLayer.h"
#include "engine/PrimitiveFactory.h"
#include "engine/Sprite.h"
#include "engine/Texture.h"
#include "engine/TextureAtlas.h"
#include "engine/Tilemap.h"
#include "engine/UIElement.h"
#include "core/Logger.h"

namespace simple_game {

GameScene::GameScene()
    : m_player(nullptr) {
}

bool GameScene::build() {
    simple_engine::Logger::info("Building GameScene after renderer and OpenGL initialization.");

    const std::shared_ptr<simple_engine::Mesh> triangleMesh = simple_engine::PrimitiveFactory::createTriangle();
    const std::shared_ptr<simple_engine::Shader> shader = getDefaultShader();
    if (!shader) {
        simple_engine::Logger::error("GameScene could not create the default shader.");
        return false;
    }

    std::shared_ptr<simple_engine::Texture> checkerTexture = std::make_shared<simple_engine::Texture>();
    const std::string texturePath = std::string(SIMPLE_ENGINE_ASSET_ROOT) + "/checker.ppm";
    if (!checkerTexture->loadFromFile(texturePath)) {
        checkerTexture.reset();
    }

    addParallaxLayer(simple_engine::ParallaxLayer(checkerTexture, glm::vec2(0.0f, 2.2f), glm::vec2(8.5f, 3.5f), 0.10f, glm::vec4(0.70f, 0.82f, 1.00f, 1.0f), -30));
    addParallaxLayer(simple_engine::ParallaxLayer(checkerTexture, glm::vec2(0.0f, 1.2f), glm::vec2(7.0f, 2.4f), 0.35f, glm::vec4(0.55f, 0.68f, 0.86f, 1.0f), -20));
    addParallaxLayer(simple_engine::ParallaxLayer(checkerTexture, glm::vec2(0.0f, 0.2f), glm::vec2(6.0f, 1.8f), 0.60f, glm::vec4(0.42f, 0.52f, 0.68f, 1.0f), -10));

    addUIElement(simple_engine::UIElement(checkerTexture, glm::vec2(20.0f, 20.0f), glm::vec2(180.0f, 28.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.18f, 0.22f, 0.30f, 0.95f), 1000));
    addUIElement(simple_engine::UIElement(checkerTexture, glm::vec2(24.0f, 24.0f), glm::vec2(120.0f, 20.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(0.92f, 0.28f, 0.24f, 0.95f), 1001));
    addUIElement(simple_engine::UIElement(checkerTexture, glm::vec2(20.0f, 56.0f), glm::vec2(32.0f, 32.0f), simple_engine::UIAnchor::TopLeft, glm::vec4(1.0f), 1002));

    const std::shared_ptr<simple_engine::Material> orangeMaterial = std::make_shared<simple_engine::Material>(shader, glm::vec4(0.95f, 0.55f, 0.20f, 1.0f));
    const std::shared_ptr<simple_engine::Material> blueMaterial = std::make_shared<simple_engine::Material>(shader, glm::vec4(0.35f, 0.85f, 1.0f, 1.0f));
    const std::shared_ptr<simple_engine::Material> greenMaterial = std::make_shared<simple_engine::Material>(shader, glm::vec4(0.45f, 1.0f, 0.55f, 1.0f));

    simple_engine::Transform playerTransform;
    playerTransform.position = { 0.0f, 1.5f };
    playerTransform.scale = { 1.0f, 1.0f };
    m_player = &createRenderObject(triangleMesh, orangeMaterial, playerTransform, 1.0f);

    simple_engine::Transform leftTransform;
    leftTransform.position = { -0.9f, 0.45f };
    leftTransform.scale = { 0.65f, 0.65f };
    createRenderObject(triangleMesh, blueMaterial, leftTransform, -0.7f);

    simple_engine::Transform spriteTransform;
    spriteTransform.position = { 0.95f, -0.35f };
    spriteTransform.scale = { 0.85f, 1.1f };
    createSprite(checkerTexture, spriteTransform, glm::vec4(1.0f), 0.45f);

    simple_engine::Transform topTransform;
    topTransform.position = { 0.35f, 0.8f };
    topTransform.scale = { 0.55f, 0.55f };
    createRenderObject(simple_engine::Sprite::getSharedQuadMesh(), greenMaterial, topTransform, -0.3f);

    simple_engine::TextureAtlas tileAtlas(checkerTexture, 2, 2);
    simple_engine::Tilemap collisionTilemap(tileAtlas, 8, 6, glm::vec2(0.5f, 0.5f), glm::vec2(-2.0f, 2.0f));
    collisionTilemap.setRenderLayer(0);

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

    simple_engine::Tilemap& worldTilemap = addTilemap(collisionTilemap);
    getCamera().setDeadZone(glm::vec2(0.75f, 0.45f));
    const simple_engine::AABB worldBounds = worldTilemap.getWorldBounds();
    getCamera().setBounds(worldBounds.min, worldBounds.max);

    simple_engine::Logger::info("GameScene build completed successfully.");
    return true;
}

void GameScene::update(float deltaTime) {
    if (m_player != nullptr) {
        getCamera().setFollowTarget(m_player->transform.position);
    } else {
        getCamera().clearFollowTarget();
    }

    simple_engine::Scene::update(deltaTime);
}

simple_engine::RenderObject* GameScene::getPlayer() const {
    return m_player;
}

} // namespace simple_game
