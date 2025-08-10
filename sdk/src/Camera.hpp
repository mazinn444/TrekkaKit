#pragma once
#include "Common.hpp"
#include <SFML/Graphics.hpp>

namespace Trekka {

class Camera {
private:
    sf::View view;
    sf::RenderWindow* window;
    float currentZoom = 1.f;

public:
    explicit Camera(sf::RenderWindow* w) : window(w), view(window->getDefaultView()) {}

    void setPosition(float x, float y) {
        view.setCenter(x, y);
        window->setView(view);
    }

    void move(float dx, float dy) {
        view.move(dx, dy);
        window->setView(view);
    }

    void reset() {
        view = window->getDefaultView();
        window->setView(view);
        currentZoom = 1.f;
    }

    Position getPosition() {
        auto c = view.getCenter();
        return {c.x, c.y};
    }

    void zoom(float factor) {
        if (factor > 0.f) {
            view.zoom(factor);
            currentZoom *= factor;
            window->setView(view);
        }
    }

    float getZoom() const {
        return currentZoom;
    }

    sf::View& getView() {
        return view;
    }

    const sf::View& getView() const {
        return view;
    }

    void setView(const sf::View& v) {
        view = v;
        window->setView(view);
    }
};

} // namespace Trekka
