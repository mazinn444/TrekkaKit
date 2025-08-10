#pragma once
#include "Common.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Font.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

namespace Trekka {

enum class GameState { Open, Minimized, Closed };

class Game {
private:
    sf::RenderWindow window;
    std::string title_;
    bool running = true;
    int targetFPS = 60;
    Input input;
    Camera camera;
    sf::Font debugFont;
    sf::Text fpsText;
    float fpsTimer = 0;
    int fpsCounter = 0;
    int lastFPS = 0;
    float lastDelta = 0.f;
    bool showFPS = true;
    sf::Color clearColor = sf::Color::Black;
    sf::Clock deltaClock;

public:
    Game(const std::string& title, Geometry size, bool canResize, int fps = 60)
        : window(sf::VideoMode(size.width, size.height), title,
                 canResize ? sf::Style::Default : (sf::Style::Titlebar | sf::Style::Close)),
          title_(title), targetFPS(fps), input(&window), camera(&window)
    {
        window.setFramerateLimit(targetFPS);
        debugFont = loadSystemFont();
        fpsText.setFont(debugFont);
        fpsText.setCharacterSize(14);
        fpsText.setFillColor(sf::Color::White);
        fpsText.setPosition(5.f, 5.f);
    }

    bool isRunning() const { return running && window.isOpen(); }

    void pollEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) running = false;
        }
        input.update();
    }

    void clear() { window.clear(clearColor); }
    void display() { window.display(); }
    void draw(Entity& entity) { entity.draw(window); }

    void drawText(const std::string& text, float x, float y, int size = 16, sf::Color color = sf::Color::White) {
        sf::Text t(text, debugFont, size);
        t.setFillColor(color);
        t.setPosition(x, y);
        window.draw(t);
    }

    void exit() { running = false; window.close(); }

    GameState getGameState() const {
        if (!window.isOpen()) return GameState::Closed;
        if (window.hasFocus()) return GameState::Open;
        return GameState::Minimized;
    }

    std::string getGameStateString() const {
        switch (getGameState()) {
            case GameState::Open: return "Open";
            case GameState::Minimized: return "Minimized";
            default: return "Closed";
        }
    }

    Input& getInput() { return input; }
    Camera& getCamera() { return camera; }
    sf::RenderWindow& getWindow() { return window; }
    const sf::RenderWindow& getWindow() const { return window; }

    void updateFPS(float dt) {
        fpsTimer += dt;
        fpsCounter++;
        if (fpsTimer >= 1.f) {
            lastFPS = fpsCounter;
            fpsCounter = 0;
            fpsTimer = 0;
            if (showFPS) fpsText.setString("FPS: " + std::to_string(lastFPS));
        }
    }

    void drawFPS() { if (showFPS) window.draw(fpsText); }

    float restartDelta() { lastDelta = deltaClock.restart().asSeconds(); return lastDelta; }
    float getDeltaSeconds() const { return lastDelta; }

    int getFPS() const { return lastFPS; }
    int getTargetFPS() const { return targetFPS; }
    void setTargetFPS(int fps) { targetFPS = fps; window.setFramerateLimit(targetFPS); }

    bool getShowFPS() const { return showFPS; }
    void setShowFPS(bool show) { showFPS = show; }

    sf::Color getClearColor() const { return clearColor; }
    void setClearColor(const sf::Color& c) { clearColor = c; }

    Geometry getWindowSize() const {
        auto sz = window.getSize();
        return { (int)sz.x, (int)sz.y };
    }

    void setWindowSize(Geometry size) { window.setSize(sf::Vector2u(size.width, size.height)); }

    void setTitle(const std::string& t) { title_ = t; window.setTitle(t); }
    std::string getTitle() const { return title_; }

    void setFPSPosition(float x, float y) { fpsText.setPosition(x, y); }
    void setFPSSize(unsigned int s) { fpsText.setCharacterSize(s); }
    sf::Vector2f getFPSPosition() const { return fpsText.getPosition(); }
    unsigned int getFPSSize() const { return fpsText.getCharacterSize(); }

    bool hasFocus() const { return window.hasFocus(); }
    void delayMs(int ms) const { sf::sleep(sf::milliseconds(ms)); }
};

inline std::ostream& operator<<(std::ostream& os, const Game& g) {
    auto size = g.getWindowSize();
    os << "FPS: " << g.getFPS()
       << " | TargetFPS: " << g.getTargetFPS()
       << " | Window: " << size.width << "x" << size.height
       << " | State: " << g.getGameStateString()
       << " | Title: " << g.getTitle();
    return os;
}

} // namespace Trekka
