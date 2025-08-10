#pragma once
#include <SFML/Graphics.hpp>

namespace Trekka {

class Animation {
private:
    int frameWidth = 0;
    int frameHeight = 0;
    int frameCount = 1;
    float frameTime = 1.f;
    float elapsedTime = 0.f;
    int currentFrame = 0;

public:
    Animation(int fw = 0, int fh = 0, int frames = 1, float fps = 1.f)
        : frameWidth(fw), frameHeight(fh), frameCount(frames)
    {
        frameTime = (fps <= 0.f) ? 1.f : 1.f / fps;
    }

    void update(float dt) {
        elapsedTime += dt;
        if (frameCount > 1 && elapsedTime >= frameTime) {
            currentFrame = (currentFrame + 1) % frameCount;
            elapsedTime = 0.f;
        }
    }

    sf::IntRect getFrameRect() const {
        return sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight);
    }

    void reset() {
        currentFrame = 0;
        elapsedTime = 0.f;
    }

    void setFPS(float fps) {
        frameTime = (fps <= 0.f) ? 1.f : 1.f / fps;
    }

    float getFPS() const {
        return (frameTime == 0.f) ? 0.f : 1.f / frameTime;
    }

    void setFrameCount(int c) {
        frameCount = (c <= 0) ? 1 : c;
    }

    int getFrameCount() const {
        return frameCount;
    }

    void setFrameSize(int fw, int fh) {
        frameWidth = fw;
        frameHeight = fh;
    }
};

} // namespace Trekka
