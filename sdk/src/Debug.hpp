#pragma once
#include "Game.hpp"
#include "Entity.hpp"
#include <vector>
#include <iostream>

namespace Trekka {
namespace Debug {

inline void showAndUpdateFPS(Game& game, float dt) {
    game.updateFPS(dt);
    game.drawFPS();
}

inline void showCollisionBox(const Entity& e, Game& game, const sf::Color& color = sf::Color::Red) {
    e.drawCollisionBox(game.getWindow(), color);
}

inline void showCollisionBoxes(const std::vector<Entity*>& ents, Game& game, const sf::Color& color = sf::Color::Red) {
    for (auto p : ents) {
        if (p) p->drawCollisionBox(game.getWindow(), color);
    }
}

inline void toggleShowFPS(Game& game) {
    game.setShowFPS(!game.getShowFPS());
}

inline void showGrid(Game& game, int cellSize = 32, const sf::Color& color = sf::Color(50,50,50,100)) {
    auto sz = game.getWindow().getSize();
    sf::RenderWindow& w = game.getWindow();
    for (int x = 0; x < (int)sz.x; x += cellSize) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(float(x), 0.f), color),
            sf::Vertex(sf::Vector2f(float(x), float(sz.y)), color)
        };
        w.draw(line, 2, sf::Lines);
    }
    for (int y = 0; y < (int)sz.y; y += cellSize) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(0.f, float(y)), color),
            sf::Vertex(sf::Vector2f(float(sz.x), float(y)), color)
        };
        w.draw(line, 2, sf::Lines);
    }
}

inline void logEntityInfo(const Entity& e, const std::string& name = "") {
    auto pos = e.getPosition();
    auto cb = e.getCollisionBox();
    std::cout << (name.empty() ? "Entity" : name)
              << " | pos: (" << pos.x << "," << pos.y << ")"
              << " | collisionBox: (" << cb.left << "," << cb.top << " " << cb.width << "x" << cb.height << ")"
              << " | alive: " << (e.isAlive() ? "yes" : "no") << '\n';
}

} // namespace Debug
} // namespace Trekka
