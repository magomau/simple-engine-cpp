#include "Mesh.h"

#include "GLFunctions.h"
#include "core/Logger.h"

namespace simple_engine {

Mesh::Mesh()
    : m_vertexArrayObject(0)
    , m_vertexBufferObject(0)
    , m_vertexCount(0) {
}

Mesh::~Mesh() {
    destroy();
}

bool Mesh::create(const float* vertices, std::size_t floatCount, int componentsPerVertex) {
    destroy();

    if (vertices == nullptr || floatCount == 0 || componentsPerVertex <= 0) {
        Logger::error("Mesh creation received invalid vertex data.");
        return false;
    }

    gl::GenVertexArrays(1, &m_vertexArrayObject);
    gl::GenBuffers(1, &m_vertexBufferObject);

    if (m_vertexArrayObject == 0 || m_vertexBufferObject == 0) {
        Logger::error("Failed to create OpenGL buffers for mesh.");
        destroy();
        return false;
    }

    m_vertexCount = static_cast<GLsizei>(floatCount / static_cast<std::size_t>(componentsPerVertex));

    gl::BindVertexArray(m_vertexArrayObject);
    gl::BindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    gl::BufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(floatCount * sizeof(float)), vertices, GL_STATIC_DRAW);
    gl::VertexAttribPointer(0, componentsPerVertex, GL_FLOAT, GL_FALSE, componentsPerVertex * static_cast<GLint>(sizeof(float)), nullptr);
    gl::EnableVertexAttribArray(0);
    gl::BindBuffer(GL_ARRAY_BUFFER, 0);
    gl::BindVertexArray(0);

    Logger::info("Mesh created successfully.");
    return true;
}

void Mesh::draw() const {
    if (m_vertexArrayObject == 0 || m_vertexCount == 0) {
        return;
    }

    gl::BindVertexArray(m_vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);
    gl::BindVertexArray(0);
}

void Mesh::destroy() {
    if (m_vertexBufferObject != 0) {
        gl::DeleteBuffers(1, &m_vertexBufferObject);
        m_vertexBufferObject = 0;
        Logger::info("Mesh vertex buffer destroyed.");
    }

    if (m_vertexArrayObject != 0) {
        gl::DeleteVertexArrays(1, &m_vertexArrayObject);
        m_vertexArrayObject = 0;
        Logger::info("Mesh vertex array destroyed.");
    }

    m_vertexCount = 0;
}

} // namespace simple_engine
