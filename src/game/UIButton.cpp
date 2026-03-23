#include "UIButton.h"

#include <utility>

#include <SDL3/SDL_mouse.h>

#include "Game.h"
#include "engine/Input.h"
#include "engine/Scene.h"

namespace simple_game {

UIButton::UIButton()
    : m_element(nullptr)
    , m_normalTint(0.24f, 0.62f, 0.92f, 0.95f)
    , m_hoverTint(0.35f, 0.74f, 1.0f, 0.97f)
    , m_pressedTint(0.16f, 0.46f, 0.78f, 0.99f)
    , m_state(UIButtonState::Normal)
    , m_pressedInside(false) {
}

UIButton::UIButton(std::shared_ptr<simple_engine::Texture> texture, const glm::vec2& screenPosition, const glm::vec2& size, ClickCallback onClick, simple_engine::UIAnchor anchor, int renderLayer)
    : m_definition(std::move(texture), screenPosition, size, anchor, glm::vec4(0.24f, 0.62f, 0.92f, 0.95f), renderLayer)
    , m_element(nullptr)
    , m_onClick(std::move(onClick))
    , m_normalTint(0.24f, 0.62f, 0.92f, 0.95f)
    , m_hoverTint(0.35f, 0.74f, 1.0f, 0.97f)
    , m_pressedTint(0.16f, 0.46f, 0.78f, 0.99f)
    , m_state(UIButtonState::Normal)
    , m_pressedInside(false) {
}

void UIButton::initialize(simple_engine::Scene& scene) {
    m_element = &scene.addUIElement(m_definition);
    applyTint();
}

void UIButton::update(Game& game, const simple_engine::Input& input, simple_engine::Scene& scene) {
    if (!m_element) {
        return;
    }

    const bool hovered = m_element->containsScreenPoint(input.getMousePosition(), scene.getLastViewportWidth(), scene.getLastViewportHeight());

    if (input.wasMouseButtonPressed(SDL_BUTTON_LEFT)) {
        m_pressedInside = hovered;
    }

    if (m_pressedInside && input.isMouseButtonDown(SDL_BUTTON_LEFT)) {
        m_state = UIButtonState::Pressed;
    } else if (hovered) {
        m_state = UIButtonState::Hover;
    } else {
        m_state = UIButtonState::Normal;
    }

    if (input.wasMouseButtonReleased(SDL_BUTTON_LEFT)) {
        if (m_pressedInside && hovered && m_onClick) {
            m_onClick(game);
        }

        m_pressedInside = false;
        m_state = hovered ? UIButtonState::Hover : UIButtonState::Normal;
    }

    applyTint();
}

void UIButton::resetInteraction() {
    m_pressedInside = false;
    m_state = UIButtonState::Normal;
    applyTint();
}

UIButtonState UIButton::getState() const {
    return m_state;
}

simple_engine::UIElement* UIButton::getElement() const {
    return m_element;
}

void UIButton::setColors(const glm::vec4& normalTint, const glm::vec4& hoverTint, const glm::vec4& pressedTint) {
    m_normalTint = normalTint;
    m_hoverTint = hoverTint;
    m_pressedTint = pressedTint;
    applyTint();
}

void UIButton::applyTint() {
    if (!m_element) {
        return;
    }

    switch (m_state) {
    case UIButtonState::Pressed:
        m_element->setTint(m_pressedTint);
        break;
    case UIButtonState::Hover:
        m_element->setTint(m_hoverTint);
        break;
    case UIButtonState::Normal:
    default:
        m_element->setTint(m_normalTint);
        break;
    }
}

} // namespace simple_game
