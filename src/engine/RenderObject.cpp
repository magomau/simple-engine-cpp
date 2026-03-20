#include "RenderObject.h"

namespace simple_engine {

RenderObject::RenderObject()
    : rotationSpeed(0.0f)
    , tintColor(1.0f, 1.0f, 1.0f, 1.0f) {
}

RenderObject::RenderObject(std::shared_ptr<Mesh> meshValue, const Transform& initialTransform, float initialRotationSpeed, const glm::vec4& initialTintColor, std::shared_ptr<Texture> initialTexture)
    : mesh(meshValue)
    , texture(initialTexture)
    , transform(initialTransform)
    , rotationSpeed(initialRotationSpeed)
    , tintColor(initialTintColor) {
}

} // namespace simple_engine
