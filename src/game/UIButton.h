#pragma once

#include <functional>
#include <memory>

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "engine/UIElement.h"

namespace simple_engine {
class Input;
class Scene;
class Texture;
}

namespace simple_game {

class Game;

enum class UIButtonState {
    Normal,
    Hover,
    Pressed,
};

class UIButton {
public:
    using ClickCallback = std::function<void(Game&)>;

    UIButton();
    UIButton(std::shared_ptr<simple_engine::Texture> texture, const glm::vec2& screenPosition, const glm::vec2& size, ClickCallback onClick, simple_engine::UIAnchor anchor = simple_engine::UIAnchor::TopLeft, int renderLayer = 1000);

    void initialize(simple_engine::Scene& scene);
    void update(Game& game, const simple_engine::Input& input, simple_engine::Scene& scene);
    void resetInteraction();

    UIButtonState getState() const;
    simple_engine::UIElement* getElement() const;
    void setColors(const glm::vec4& normalTint, const glm::vec4& hoverTint, const glm::vec4& pressedTint);

private:
    void applyTint();

    simple_engine::UIElement m_definition;
    simple_engine::UIElement* m_element;
    ClickCallback m_onClick;
    glm::vec4 m_normalTint;
    glm::vec4 m_hoverTint;
    glm::vec4 m_pressedTint;
    UIButtonState m_state;
    bool m_pressedInside;
};

} // namespace simple_game
