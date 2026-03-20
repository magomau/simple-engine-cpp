#include "RenderObject.h"

namespace simple_engine {

RenderObject::RenderObject()
    : rotationSpeed(0.0f) {
}

RenderObject::RenderObject(const Transform& initialTransform, float initialRotationSpeed)
    : transform(initialTransform)
    , rotationSpeed(initialRotationSpeed) {
}

} // namespace simple_engine
