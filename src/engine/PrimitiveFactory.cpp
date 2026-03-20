#include "PrimitiveFactory.h"

#include <array>
#include <memory>

#include "Mesh.h"
#include "core/Logger.h"

namespace simple_engine {

std::shared_ptr<Mesh> PrimitiveFactory::createTriangle() {
    constexpr std::array<float, 15> vertices = {
         0.0f,  0.6f, 0.0f,   0.5f, 1.0f,
        -0.6f, -0.45f, 0.0f,  0.0f, 0.0f,
         0.6f, -0.45f, 0.0f,  1.0f, 0.0f,
    };

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    if (!mesh->create(vertices.data(), vertices.size(), 5, true)) {
        Logger::error("Failed to create triangle primitive.");
        return nullptr;
    }

    return mesh;
}

std::shared_ptr<Mesh> PrimitiveFactory::createQuad() {
    constexpr std::array<float, 30> vertices = {
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
    };

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    if (!mesh->create(vertices.data(), vertices.size(), 5, true)) {
        Logger::error("Failed to create quad primitive.");
        return nullptr;
    }

    return mesh;
}

} // namespace simple_engine
