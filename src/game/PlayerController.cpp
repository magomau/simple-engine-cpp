#include "PlayerController.h"

#include <glm/geometric.hpp>
#include <glm/vec2.hpp>

#include <SDL3/SDL_scancode.h>

#include "engine/Input.h"
#include "engine/RenderObject.h"
#include "engine/Scene.h"

namespace simple_game {

PlayerController::PlayerController()
    : m_moveSpeed(1.5f)
    , m_collisionScale(0.8f) {
}

void PlayerController::update(const simple_engine::Input& input, simple_engine::Scene& scene, simple_engine::RenderObject& player, float deltaTime) {
    const glm::vec2 inputDirection = getInputDirection(input);
    if (glm::length(inputDirection) <= 0.0f) {
        return;
    }

    const glm::vec2 direction = glm::normalize(inputDirection);
    scene.moveObject(player, direction * (m_moveSpeed * deltaTime), m_collisionScale);
}

void PlayerController::setMoveSpeed(float moveSpeed) {
    m_moveSpeed = moveSpeed;
}

void PlayerController::setCollisionScale(float collisionScale) {
    m_collisionScale = collisionScale;
}

float PlayerController::getMoveSpeed() const {
    return m_moveSpeed;
}

float PlayerController::getCollisionScale() const {
    return m_collisionScale;
}

glm::vec2 PlayerController::getInputDirection(const simple_engine::Input& input) const {
    glm::vec2 direction(0.0f, 0.0f);

    if (input.isKeyPressed(SDL_SCANCODE_W)) {
        direction.y += 1.0f;
    }
    if (input.isKeyPressed(SDL_SCANCODE_S)) {
        direction.y -= 1.0f;
    }
    if (input.isKeyPressed(SDL_SCANCODE_A)) {
        direction.x -= 1.0f;
    }
    if (input.isKeyPressed(SDL_SCANCODE_D)) {
        direction.x += 1.0f;
    }

    return direction;
}

} // namespace simple_game
