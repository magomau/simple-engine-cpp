#pragma once

#include <glm/vec2.hpp>

#include "TextureAtlas.h"

namespace simple_engine {

class Material;

class SpriteAnimation {
public:
    SpriteAnimation();

    void configureGrid(int frameCount, int columns, int rows, float frameDurationSeconds, bool shouldLoop = true, int startFrame = 0, const AtlasRegion& atlasRegion = AtlasRegion());
    void update(float deltaTime);
    void apply(Material& material) const;
    void reset();
    void play();
    void stop();
    void setFrame(int frameIndex);

    bool isValid() const;
    bool isPlaying() const;
    int getFrameCount() const;
    int getCurrentFrame() const;
    int getColumns() const;
    int getRows() const;
    int getStartFrame() const;
    float getFrameDuration() const;
    bool isLooping() const;
    glm::vec2 getFrameSize() const;
    const AtlasRegion& getAtlasRegion() const;

private:
    void clampCurrentFrame();

    int m_frameCount;
    int m_columns;
    int m_rows;
    int m_startFrame;
    int m_currentFrame;
    float m_frameDuration;
    float m_accumulatedTime;
    bool m_loop;
    bool m_playing;
    AtlasRegion m_atlasRegion;
};

} // namespace simple_engine
