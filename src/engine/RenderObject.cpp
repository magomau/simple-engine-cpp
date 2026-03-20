#include "RenderObject.h"

namespace simple_engine {

RenderObject::RenderObject()
    : rotationSpeed(0.0f) {
}

RenderObject::RenderObject(std::shared_ptr<Mesh> meshValue, std::shared_ptr<Material> materialValue, const Transform& initialTransform, float initialRotationSpeed)
    : mesh(meshValue)
    , material(materialValue)
    , transform(initialTransform)
    , rotationSpeed(initialRotationSpeed) {
}

} // namespace simple_engine
