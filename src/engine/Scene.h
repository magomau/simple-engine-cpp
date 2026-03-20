#pragma once

#include <vector>

#include "RenderObject.h"

namespace simple_engine {

class Scene {
public:
    Scene();

    void update(float deltaTime);

    const std::vector<RenderObject>& getObjects() const;
    RenderObject* getPrimaryObject();

private:
    std::vector<RenderObject> m_objects;
};

} // namespace simple_engine
