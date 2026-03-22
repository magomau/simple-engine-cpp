#pragma once

#include "engine/Scene.h"

namespace simple_engine {
class RenderObject;
}

namespace simple_game {

class GameScene : public simple_engine::Scene {
public:
    GameScene();

    bool build();
    void update(float deltaTime) override;
    simple_engine::RenderObject* getPlayer() const;

private:
    simple_engine::RenderObject* m_player;
};

} // namespace simple_game
