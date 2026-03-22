#include "RenderObject.h"

namespace simple_engine {

RenderObject::RenderObject()
    : rotationSpeed(0.0f)
    , renderLayer(0) {
}

RenderObject::RenderObject(std::shared_ptr<Mesh> meshValue, std::shared_ptr<Material> materialValue, const Transform& initialTransform, float initialRotationSpeed, int initialRenderLayer)
    : mesh(meshValue)
    , material(materialValue)
    , transform(initialTransform)
    , rotationSpeed(initialRotationSpeed)
    , renderLayer(initialRenderLayer) {
}

void RenderObject::update(float deltaTime) {
    transform.rotation += rotationSpeed * deltaTime;
}

} // namespace simple_engine
