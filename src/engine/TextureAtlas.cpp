#include "TextureAtlas.h"

#include <algorithm>

namespace simple_engine {

AtlasRegion::AtlasRegion()
    : minUV(0.0f, 0.0f)
    , maxUV(1.0f, 1.0f) {
}

AtlasRegion::AtlasRegion(const glm::vec2& minUVValue, const glm::vec2& maxUVValue)
    : minUV(minUVValue)
    , maxUV(maxUVValue) {
}

bool AtlasRegion::isValid() const {
    return minUV.x >= 0.0f && minUV.y >= 0.0f
        && maxUV.x <= 1.0f && maxUV.y <= 1.0f
        && maxUV.x > minUV.x && maxUV.y > minUV.y;
}

glm::vec2 AtlasRegion::getSize() const {
    return maxUV - minUV;
}

TextureAtlas::TextureAtlas()
    : m_columns(1)
    , m_rows(1) {
}

TextureAtlas::TextureAtlas(std::shared_ptr<Texture> texture, int columns, int rows)
    : m_texture(std::move(texture))
    , m_columns(std::max(columns, 1))
    , m_rows(std::max(rows, 1)) {
}

void TextureAtlas::setTexture(std::shared_ptr<Texture> texture) {
    m_texture = std::move(texture);
}

void TextureAtlas::configureGrid(int columns, int rows) {
    m_columns = std::max(columns, 1);
    m_rows = std::max(rows, 1);
}

bool TextureAtlas::isValid() const {
    return m_texture != nullptr && m_columns > 0 && m_rows > 0;
}

std::shared_ptr<Texture> TextureAtlas::getTexture() const {
    return m_texture;
}

AtlasRegion TextureAtlas::getFullRegion() const {
    return AtlasRegion();
}

AtlasRegion TextureAtlas::getRegion(int column, int row, int widthInCells, int heightInCells) const {
    const int clampedColumn = std::clamp(column, 0, m_columns - 1);
    const int clampedRow = std::clamp(row, 0, m_rows - 1);
    const int clampedWidth = std::clamp(widthInCells, 1, m_columns - clampedColumn);
    const int clampedHeight = std::clamp(heightInCells, 1, m_rows - clampedRow);

    const glm::vec2 cellSize(1.0f / static_cast<float>(m_columns), 1.0f / static_cast<float>(m_rows));
    const glm::vec2 minUV(
        static_cast<float>(clampedColumn) * cellSize.x,
        static_cast<float>(clampedRow) * cellSize.y);
    const glm::vec2 maxUV(
        minUV.x + (cellSize.x * static_cast<float>(clampedWidth)),
        minUV.y + (cellSize.y * static_cast<float>(clampedHeight)));

    return AtlasRegion(minUV, maxUV);
}

AtlasRegion TextureAtlas::getRegionByIndex(int index, int widthInCells, int heightInCells) const {
    const int clampedIndex = std::clamp(index, 0, (m_columns * m_rows) - 1);
    const int column = clampedIndex % m_columns;
    const int row = clampedIndex / m_columns;
    return getRegion(column, row, widthInCells, heightInCells);
}

} // namespace simple_engine
