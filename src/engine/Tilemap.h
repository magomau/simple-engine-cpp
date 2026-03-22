#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>

#include "Collision.h"
#include "Sprite.h"
#include "TextureAtlas.h"

namespace simple_engine {

class Shader;

class Tilemap {
public:
    Tilemap();
    Tilemap(const TextureAtlas& atlas, int width, int height, const glm::vec2& tileSize = glm::vec2(1.0f), const glm::vec2& position = glm::vec2(0.0f));

    void initialize(std::shared_ptr<Shader> shader);
    void setTile(int x, int y, int atlasIndex);
    void setTiles(const std::vector<int>& tiles);
    void setTileSolid(int x, int y, bool solid);
    int getTile(int x, int y) const;
    bool isTileSolid(int x, int y) const;
    bool blocksCell(int x, int y) const;
    bool collidesWithAABB(const AABB& bounds) const;

    void setPosition(const glm::vec2& position);
    void setTileSize(const glm::vec2& tileSize);

    int getWidth() const;
    int getHeight() const;
    const glm::vec2& getPosition() const;
    const glm::vec2& getTileSize() const;
    AABB getWorldBounds() const;
    const std::vector<std::shared_ptr<Sprite>>& getSprites() const;

    bool isDirty() const;
    void clearDirty();

private:
    bool isCoordinateValid(int x, int y) const;
    int getTileIndex(int x, int y) const;
    void rebuildSprites();

    TextureAtlas m_atlas;
    std::shared_ptr<Shader> m_shader;
    std::vector<int> m_tiles;
    std::vector<bool> m_solidTiles;
    std::vector<std::shared_ptr<Sprite>> m_sprites;
    glm::vec2 m_position;
    glm::vec2 m_tileSize;
    int m_width;
    int m_height;
    bool m_dirty;
};

} // namespace simple_engine
