#include "SpriteAnimation.h"

#include <algorithm>

#include "Material.h"

namespace simple_engine {

SpriteAnimation::SpriteAnimation()
    : m_frameCount(1)
    , m_columns(1)
    , m_rows(1)
    , m_startFrame(0)
    , m_currentFrame(0)
    , m_frameDuration(0.1f)
    , m_accumulatedTime(0.0f)
    , m_loop(true)
    , m_playing(false) {
}

void SpriteAnimation::configureGrid(int frameCount, int columns, int rows, float frameDurationSeconds, bool shouldLoop, int startFrame) {
    m_columns = std::max(columns, 1);
    m_rows = std::max(rows, 1);
    const int totalFrames = m_columns * m_rows;

    m_frameCount = std::clamp(frameCount, 1, totalFrames);
    m_frameDuration = std::max(frameDurationSeconds, 0.0001f);
    m_loop = shouldLoop;
    m_startFrame = std::clamp(startFrame, 0, totalFrames - m_frameCount);
    m_currentFrame = m_startFrame;
    m_accumulatedTime = 0.0f;
    m_playing = true;

    clampCurrentFrame();
}

void SpriteAnimation::update(float deltaTime) {
    if (!isValid() || !m_playing) {
        return;
    }

    m_accumulatedTime += std::max(deltaTime, 0.0f);
    while (m_accumulatedTime >= m_frameDuration) {
        m_accumulatedTime -= m_frameDuration;

        const int localFrame = (m_currentFrame - m_startFrame) + 1;
        if (localFrame >= m_frameCount) {
            if (m_loop) {
                m_currentFrame = m_startFrame;
                continue;
            }

            m_currentFrame = m_startFrame + (m_frameCount - 1);
            m_playing = false;
            m_accumulatedTime = 0.0f;
            break;
        }

        m_currentFrame = m_startFrame + localFrame;
    }
}

void SpriteAnimation::apply(Material& material) const {
    if (!isValid()) {
        material.resetTextureRegion();
        return;
    }

    const glm::vec2 frameSize = getFrameSize();
    const int column = m_currentFrame % m_columns;
    const int row = m_currentFrame / m_columns;

    const glm::vec2 minUV(
        static_cast<float>(column) * frameSize.x,
        static_cast<float>(row) * frameSize.y);
    const glm::vec2 maxUV = minUV + frameSize;

    material.setTextureRegion(minUV, maxUV);
}

void SpriteAnimation::reset() {
    m_currentFrame = m_startFrame;
    m_accumulatedTime = 0.0f;
}

void SpriteAnimation::play() {
    if (!isValid()) {
        return;
    }

    m_playing = true;
}

void SpriteAnimation::stop() {
    m_playing = false;
}

void SpriteAnimation::setFrame(int frameIndex) {
    if (!isValid()) {
        m_currentFrame = 0;
        return;
    }

    m_currentFrame = std::clamp(frameIndex, m_startFrame, m_startFrame + m_frameCount - 1);
    m_accumulatedTime = 0.0f;
}

bool SpriteAnimation::isValid() const {
    return m_frameCount > 0 && m_columns > 0 && m_rows > 0 && m_startFrame >= 0 && (m_startFrame + m_frameCount) <= (m_columns * m_rows);
}

bool SpriteAnimation::isPlaying() const {
    return m_playing;
}

int SpriteAnimation::getFrameCount() const {
    return m_frameCount;
}

int SpriteAnimation::getCurrentFrame() const {
    return m_currentFrame;
}

float SpriteAnimation::getFrameDuration() const {
    return m_frameDuration;
}

bool SpriteAnimation::isLooping() const {
    return m_loop;
}

glm::vec2 SpriteAnimation::getFrameSize() const {
    return glm::vec2(1.0f / static_cast<float>(m_columns), 1.0f / static_cast<float>(m_rows));
}

void SpriteAnimation::clampCurrentFrame() {
    if (!isValid()) {
        m_currentFrame = 0;
        return;
    }

    m_currentFrame = std::clamp(m_currentFrame, m_startFrame, m_startFrame + m_frameCount - 1);
}

} // namespace simple_engine
