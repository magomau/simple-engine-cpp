#include "Tilemap.h"

#include <algorithm>
#include <memory>

#include "Shader.h"

namespace simple_engine {

Tilemap::Tilemap()
    : m_position(0.0f, 0.0f)
    , m_tileSize(1.0f, 1.0f)
    , m_width(0)
    , m_height(0)
    , m_dirty(false) {
}

Tilemap::Tilemap(const TextureAtlas& atlas, int width, int height, const glm::vec2& tileSize, const glm::vec2& position)
    : m_atlas(atlas)
    , m_position(position)
    , m_tileSize(tileSize)
    , m_width(std::max(width, 0))
    , m_height(std::max(height, 0))
    , m_dirty(false) {
    m_tiles.resize(static_cast<std::size_t>(m_width * m_height), -1);
}

void Tilemap::initialize(std::shared_ptr<Shader> shader) {
    m_shader = std::move(shader);
    rebuildSprites();
}

void Tilemap::setTile(int x, int y, int atlasIndex) {
    if (!isCoordinateValid(x, y)) {
        return;
    }

    m_tiles[static_cast<std::size_t>(getTileIndex(x, y))] = atlasIndex;
    rebuildSprites();
}

void Tilemap::setTiles(const std::vector<int>& tiles) {
    const std::size_t expectedTileCount = static_cast<std::size_t>(m_width * m_height);
    if (tiles.size() != expectedTileCount) {
        return;
    }

    m_tiles = tiles;
    rebuildSprites();
}

int Tilemap::getTile(int x, int y) const {
    if (!isCoordinateValid(x, y)) {
        return -1;
    }

    return m_tiles[static_cast<std::size_t>(getTileIndex(x, y))];
}

void Tilemap::setPosition(const glm::vec2& position) {
    m_position = position;
    rebuildSprites();
}

void Tilemap::setTileSize(const glm::vec2& tileSize) {
    m_tileSize = tileSize;
    rebuildSprites();
}

int Tilemap::getWidth() const {
    return m_width;
}

int Tilemap::getHeight() const {
    return m_height;
}

const glm::vec2& Tilemap::getPosition() const {
    return m_position;
}

const glm::vec2& Tilemap::getTileSize() const {
    return m_tileSize;
}

const std::vector<std::shared_ptr<Sprite>>& Tilemap::getSprites() const {
    return m_sprites;
}

bool Tilemap::isDirty() const {
    return m_dirty;
}

void Tilemap::clearDirty() {
    m_dirty = false;
}

bool Tilemap::isCoordinateValid(int x, int y) const {
    return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

int Tilemap::getTileIndex(int x, int y) const {
    return y * m_width + x;
}

void Tilemap::rebuildSprites() {
    m_sprites.clear();

    if (!m_shader || !m_atlas.getTexture()) {
        m_dirty = true;
        return;
    }

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            const int atlasIndex = getTile(x, y);
            if (atlasIndex < 0) {
                continue;
            }

            Transform tileTransform;
            tileTransform.position = glm::vec2(
                m_position.x + (static_cast<float>(x) * m_tileSize.x) + (m_tileSize.x * 0.5f),
                m_position.y - (static_cast<float>(y) * m_tileSize.y) - (m_tileSize.y * 0.5f));
            tileTransform.scale = m_tileSize;

            std::shared_ptr<Sprite> sprite = Sprite::create(m_shader, m_atlas.getTexture(), tileTransform);
            if (!sprite) {
                continue;
            }

            sprite->setAtlasRegionByIndex(m_atlas, atlasIndex);
            m_sprites.push_back(sprite);
        }
    }

    m_dirty = true;
}

} // namespace simple_engine
