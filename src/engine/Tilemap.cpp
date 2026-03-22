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
    , m_renderLayer(0)
    , m_dirty(false) {
}

Tilemap::Tilemap(const TextureAtlas& atlas, int width, int height, const glm::vec2& tileSize, const glm::vec2& position)
    : m_atlas(atlas)
    , m_position(position)
    , m_tileSize(tileSize)
    , m_width(std::max(width, 0))
    , m_height(std::max(height, 0))
    , m_renderLayer(0)
    , m_dirty(false) {
    m_tiles.resize(static_cast<std::size_t>(m_width * m_height), -1);
    m_solidTiles.resize(static_cast<std::size_t>(m_width * m_height), false);
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

void Tilemap::setTileSolid(int x, int y, bool solid) {
    if (!isCoordinateValid(x, y)) {
        return;
    }

    m_solidTiles[static_cast<std::size_t>(getTileIndex(x, y))] = solid;
}

int Tilemap::getTile(int x, int y) const {
    if (!isCoordinateValid(x, y)) {
        return -1;
    }

    return m_tiles[static_cast<std::size_t>(getTileIndex(x, y))];
}

bool Tilemap::isTileSolid(int x, int y) const {
    if (!isCoordinateValid(x, y)) {
        return false;
    }

    return m_solidTiles[static_cast<std::size_t>(getTileIndex(x, y))];
}

bool Tilemap::blocksCell(int x, int y) const {
    return getTile(x, y) >= 0 && isTileSolid(x, y);
}

bool Tilemap::collidesWithAABB(const AABB& bounds) const {
    if (m_tileSize.x <= 0.0f || m_tileSize.y <= 0.0f || m_width <= 0 || m_height <= 0) {
        return false;
    }

    const int startX = std::max(0, static_cast<int>((bounds.min.x - m_position.x) / m_tileSize.x));
    const int endX = std::min(m_width - 1, static_cast<int>((bounds.max.x - m_position.x) / m_tileSize.x));
    const int startY = std::max(0, static_cast<int>((m_position.y - bounds.max.y) / m_tileSize.y));
    const int endY = std::min(m_height - 1, static_cast<int>((m_position.y - bounds.min.y) / m_tileSize.y));

    for (int y = startY; y <= endY; ++y) {
        for (int x = startX; x <= endX; ++x) {
            if (!blocksCell(x, y)) {
                continue;
            }

            const float tileMinX = m_position.x + (static_cast<float>(x) * m_tileSize.x);
            const float tileMaxX = tileMinX + m_tileSize.x;
            const float tileMaxY = m_position.y - (static_cast<float>(y) * m_tileSize.y);
            const float tileMinY = tileMaxY - m_tileSize.y;
            const AABB tileBounds(glm::vec2(tileMinX, tileMinY), glm::vec2(tileMaxX, tileMaxY));

            if (bounds.intersects(tileBounds)) {
                return true;
            }
        }
    }

    return false;
}

void Tilemap::setPosition(const glm::vec2& position) {
    m_position = position;
    rebuildSprites();
}

void Tilemap::setTileSize(const glm::vec2& tileSize) {
    m_tileSize = tileSize;
    rebuildSprites();
}

void Tilemap::setRenderLayer(int renderLayer) {
    m_renderLayer = renderLayer;

    for (const std::shared_ptr<Sprite>& sprite : m_sprites) {
        if (!sprite) {
            continue;
        }

        sprite->renderLayer = m_renderLayer;
    }

    m_dirty = true;
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

AABB Tilemap::getWorldBounds() const {
    const glm::vec2 minBounds = m_position + glm::vec2(0.0f, -static_cast<float>(m_height) * m_tileSize.y);
    const glm::vec2 maxBounds = m_position + glm::vec2(static_cast<float>(m_width) * m_tileSize.x, 0.0f);
    return AABB(minBounds, maxBounds);
}

const std::vector<std::shared_ptr<Sprite>>& Tilemap::getSprites() const {
    return m_sprites;
}

int Tilemap::getRenderLayer() const {
    return m_renderLayer;
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
            sprite->renderLayer = m_renderLayer;
            m_sprites.push_back(sprite);
        }
    }

    m_dirty = true;
}

} // namespace simple_engine
