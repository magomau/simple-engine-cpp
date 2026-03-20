#pragma once

#include <memory>

namespace simple_engine {

class Mesh;

class PrimitiveFactory {
public:
    static std::shared_ptr<Mesh> createTriangle();
    static std::shared_ptr<Mesh> createQuad();
};

} // namespace simple_engine
