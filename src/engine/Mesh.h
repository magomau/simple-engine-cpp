#pragma once

#include <cstddef>

#include <SDL3/SDL_opengl.h>

namespace simple_engine {

class Mesh {
public:
    Mesh();
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    bool create(const float* vertices, std::size_t floatCount, int componentsPerVertex);
    void draw() const;
    void destroy();

private:
    GLuint m_vertexArrayObject;
    GLuint m_vertexBufferObject;
    GLsizei m_vertexCount;
};

} // namespace simple_engine
