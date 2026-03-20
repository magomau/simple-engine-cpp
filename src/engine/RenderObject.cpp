#include "RenderObject.h"

namespace simple_engine {

RenderObject::RenderObject()
    : rotationSpeed(0.0f) {
}

RenderObject::RenderObject(std::shared_ptr<Mesh> meshValue, const Transform& initialTransform, float initialRotationSpeed)
    : mesh(meshValue)
    , transform(initialTransform)
    , rotationSpeed(initialRotationSpeed) {
}

} // namespace simple_engine
