#include "Texture.h"

#include <fstream>
#include <string>
#include <vector>

#include "GLFunctions.h"
#include "core/Logger.h"

namespace simple_engine {

namespace {

bool readNextToken(std::ifstream& file, std::string& token) {
    while (file >> token) {
        if (!token.empty() && token[0] == '#') {
            std::string ignoredLine;
            std::getline(file, ignoredLine);
            continue;
        }
        return true;
    }
    return false;
}

} // namespace

Texture::Texture()
    : m_textureId(0) {
}

Texture::~Texture() {
    destroy();
}

bool Texture::loadFromFile(const std::string& filePath) {
    destroy();

    std::ifstream file(filePath);
    if (!file.is_open()) {
        Logger::error("Failed to open texture file.");
        return false;
    }

    std::string token;
    if (!readNextToken(file, token) || token != "P3") {
        Logger::error("Texture loader currently supports only ASCII PPM (P3).");
        return false;
    }

    if (!readNextToken(file, token)) {
        Logger::error("Failed to read texture width.");
        return false;
    }
    const int width = std::stoi(token);

    if (!readNextToken(file, token)) {
        Logger::error("Failed to read texture height.");
        return false;
    }
    const int height = std::stoi(token);

    if (!readNextToken(file, token)) {
        Logger::error("Failed to read texture max value.");
        return false;
    }
    const int maxValue = std::stoi(token);
    if (width <= 0 || height <= 0 || maxValue <= 0) {
        Logger::error("Texture file contains invalid dimensions or max value.");
        return false;
    }

    std::vector<unsigned char> pixels(static_cast<std::size_t>(width * height * 3));
    for (std::size_t index = 0; index < pixels.size(); ++index) {
        if (!readNextToken(file, token)) {
            Logger::error("Texture file ended before all pixel data was read.");
            return false;
        }

        const int value = std::stoi(token);
        pixels[index] = static_cast<unsigned char>((value * 255) / maxValue);
    }

    glGenTextures(1, &m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());
    glBindTexture(GL_TEXTURE_2D, 0);

    Logger::info("Texture loaded successfully.");
    return true;
}

void Texture::bind(unsigned int slot) const {
    gl::ActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Texture::destroy() {
    if (m_textureId != 0) {
        glDeleteTextures(1, &m_textureId);
        m_textureId = 0;
        Logger::info("Texture destroyed.");
    }
}

} // namespace simple_engine
