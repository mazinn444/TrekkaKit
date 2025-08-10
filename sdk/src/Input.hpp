#pragma once
#include "Common.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

namespace Trekka {

class Input {
private:
    sf::RenderWindow* window;
    std::vector<bool> currentKeys;
    std::vector<bool> previousKeys;
    std::vector<bool> currentMouseButtons;
    std::vector<bool> previousMouseButtons;

public:
    explicit Input(sf::RenderWindow* w)
        : window(w),
          currentKeys(256, false), previousKeys(256, false),
          currentMouseButtons(5, false), previousMouseButtons(5, false)
    {}

    inline static const std::map<Key, sf::Keyboard::Key> keyMap = {
        {Key::A, sf::Keyboard::A}, {Key::B, sf::Keyboard::B}, {Key::C, sf::Keyboard::C}, {Key::D, sf::Keyboard::D},
        {Key::E, sf::Keyboard::E}, {Key::F, sf::Keyboard::F}, {Key::G, sf::Keyboard::G}, {Key::H, sf::Keyboard::H},
        {Key::I, sf::Keyboard::I}, {Key::J, sf::Keyboard::J}, {Key::K, sf::Keyboard::K}, {Key::L, sf::Keyboard::L},
        {Key::M, sf::Keyboard::M}, {Key::N, sf::Keyboard::N}, {Key::O, sf::Keyboard::O}, {Key::P, sf::Keyboard::P},
        {Key::Q, sf::Keyboard::Q}, {Key::R, sf::Keyboard::R}, {Key::S, sf::Keyboard::S}, {Key::T, sf::Keyboard::T},
        {Key::U, sf::Keyboard::U}, {Key::V, sf::Keyboard::V}, {Key::W, sf::Keyboard::W}, {Key::X, sf::Keyboard::X},
        {Key::Y, sf::Keyboard::Y}, {Key::Z, sf::Keyboard::Z},
        {Key::Left, sf::Keyboard::Left}, {Key::Right, sf::Keyboard::Right},
        {Key::Up, sf::Keyboard::Up}, {Key::Down, sf::Keyboard::Down},
        {Key::Space, sf::Keyboard::Space}, {Key::Escape, sf::Keyboard::Escape},
        {Key::Enter, sf::Keyboard::Enter}
    };

    inline static const std::map<MouseButton, sf::Mouse::Button> mouseMap = {
        {MouseButton::Left, sf::Mouse::Left},
        {MouseButton::Right, sf::Mouse::Right},
        {MouseButton::Middle, sf::Mouse::Middle}
    };

    inline int toKeyCode(sf::Keyboard::Key k) const { return static_cast<int>(k); }

    inline int mouseButtonIndex(sf::Mouse::Button b) const {
        switch (b) {
            case sf::Mouse::Left: return 0;
            case sf::Mouse::Right: return 1;
            case sf::Mouse::Middle: return 2;
            default: return -1;
        }
    }

    void update() {
        previousKeys = currentKeys;
        previousMouseButtons = currentMouseButtons;

        for (const auto& kv : keyMap) {
            int code = toKeyCode(kv.second);
            if (code >= 0 && code < (int)currentKeys.size()) {
                currentKeys[code] = sf::Keyboard::isKeyPressed(kv.second);
            }
        }

        currentMouseButtons[0] = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        currentMouseButtons[1] = sf::Mouse::isButtonPressed(sf::Mouse::Right);
        currentMouseButtons[2] = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
    }

    bool isKeyPressed(Key key) const {
        auto it = keyMap.find(key);
        if (it == keyMap.end()) return false;
        int code = toKeyCode(it->second);
        if (code < 0 || code >= (int)currentKeys.size()) return false;
        return currentKeys[code];
    }

    bool isKeyClick(Key key) const {
        auto it = keyMap.find(key);
        if (it == keyMap.end()) return false;
        int code = toKeyCode(it->second);
        if (code < 0 || code >= (int)currentKeys.size()) return false;
        return currentKeys[code] && !previousKeys[code];
    }

    bool isMousePressed(MouseButton btn) const {
        auto it = mouseMap.find(btn);
        if (it == mouseMap.end()) return false;
        int idx = mouseButtonIndex(it->second);
        if (idx < 0 || idx >= (int)currentMouseButtons.size()) return false;
        return currentMouseButtons[idx];
    }

    bool isMouseClick(MouseButton btn) const {
        auto it = mouseMap.find(btn);
        if (it == mouseMap.end()) return false;
        int idx = mouseButtonIndex(it->second);
        if (idx < 0 || idx >= (int)currentMouseButtons.size()) return false;
        return currentMouseButtons[idx] && !previousMouseButtons[idx];
    }

    Position getMousePosition() const {
        auto p = sf::Mouse::getPosition(*window);
        return Position(static_cast<float>(p.x), static_cast<float>(p.y));
    }

    float getMouseWheelDelta(const sf::Event& ev) const {
        return ev.type == sf::Event::MouseWheelScrolled ? ev.mouseWheelScroll.delta : 0.f;
    }
};

} // namespace Trekka
