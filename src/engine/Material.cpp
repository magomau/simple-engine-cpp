#include "Material.h"

#include <memory>

namespace simple_engine {

namespace {

constexpr const char* kVertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec2 uUVOffset;
uniform vec2 uUVScale;

out vec2 vTexCoord;

void main() {
    vTexCoord = (aTexCoord * uUVScale) + uUVOffset;
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
)";

constexpr const char* kFragmentShaderSource = R"(
#version 330 core
in vec2 vTexCoord;
out vec4 fragmentColor;

uniform vec4 uBaseColor;
uniform int uUseTexture;
uniform sampler2D uTexture0;

void main() {
    vec4 color = uBaseColor;
    if (uUseTexture == 1) {
        color *= texture(uTexture0, vTexCoord);
    }
    fragmentColor = color;
}
)";

} // namespace

Material::Material()
    : baseColor(1.0f, 1.0f, 1.0f, 1.0f)
    , uvOffset(0.0f, 0.0f)
    , uvScale(1.0f, 1.0f) {
}

Material::Material(std::shared_ptr<Shader> shaderValue, const glm::vec4& baseColorValue, std::shared_ptr<Texture> textureValue)
    : shader(shaderValue)
    , texture(textureValue)
    , baseColor(baseColorValue)
    , uvOffset(0.0f, 0.0f)
    , uvScale(1.0f, 1.0f) {
}

void Material::apply(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) const {
    if (!isValid()) {
        return;
    }

    shader->bind();
    shader->setMatrix4("uModel", model);
    shader->setMatrix4("uView", view);
    shader->setMatrix4("uProjection", projection);
    shader->setVector2("uUVOffset", uvOffset);
    shader->setVector2("uUVScale", uvScale);
    shader->setVector4("uBaseColor", baseColor);
    shader->setInt("uTexture0", 0);
    shader->setInt("uUseTexture", texture ? 1 : 0);

    if (texture) {
        texture->bind(0);
    }
}

bool Material::isValid() const {
    return shader != nullptr;
}

void Material::setTextureRegion(const glm::vec2& minUV, const glm::vec2& maxUV) {
    uvOffset = minUV;
    uvScale = maxUV - minUV;
}

void Material::resetTextureRegion() {
    uvOffset = glm::vec2(0.0f, 0.0f);
    uvScale = glm::vec2(1.0f, 1.0f);
}

std::shared_ptr<Shader> Material::createDefaultShader() {
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();
    if (!shader->create(kVertexShaderSource, kFragmentShaderSource)) {
        return nullptr;
    }
    return shader;
}

} // namespace simple_engine
