#pragma once

#include <memory>
#include <string>

#include <SDL3/SDL_opengl.h>

namespace simple_engine {

class Texture {
public:
    Texture();
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    bool loadFromFile(const std::string& filePath);
    void bind(unsigned int slot = 0) const;
    void destroy();

private:
    GLuint m_textureId;
};

} // namespace simple_engine
