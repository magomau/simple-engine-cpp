#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include "Texture.h"

namespace simple_engine {

struct AtlasRegion {
    glm::vec2 minUV;
    glm::vec2 maxUV;

    AtlasRegion();
    AtlasRegion(const glm::vec2& minUVValue, const glm::vec2& maxUVValue);

    bool isValid() const;
    glm::vec2 getSize() const;
};

class TextureAtlas {
public:
    TextureAtlas();
    TextureAtlas(std::shared_ptr<Texture> texture, int columns, int rows);

    void setTexture(std::shared_ptr<Texture> texture);
    void configureGrid(int columns, int rows);

    bool isValid() const;
    std::shared_ptr<Texture> getTexture() const;
    AtlasRegion getFullRegion() const;
    AtlasRegion getRegion(int column, int row, int widthInCells = 1, int heightInCells = 1) const;
    AtlasRegion getRegionByIndex(int index, int widthInCells = 1, int heightInCells = 1) const;

private:
    std::shared_ptr<Texture> m_texture;
    int m_columns;
    int m_rows;
};

} // namespace simple_engine
