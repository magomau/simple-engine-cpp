#pragma once

#include <memory>

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Shader.h"
#include "Texture.h"

namespace simple_engine {

class Material {
public:
    Material();
    Material(std::shared_ptr<Shader> shader, const glm::vec4& baseColor, std::shared_ptr<Texture> texture = nullptr);

    void apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const;
    bool isValid() const;
    void setTextureRegion(const glm::vec2& minUV, const glm::vec2& maxUV);
    void resetTextureRegion();

    static std::shared_ptr<Shader> createDefaultShader();

    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;
    glm::vec4 baseColor;
    glm::vec2 uvOffset;
    glm::vec2 uvScale;
};

} // namespace simple_engine
