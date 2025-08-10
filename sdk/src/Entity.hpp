#pragma once
#include "Common.hpp"
#include "Animation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Trekka {

class Entity {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    Box hitbox;
    bool alive = true;
    Animation* animation = nullptr;
    float rotation = 0.f, scaleX = 1.f, scaleY = 1.f;
    bool flipHorizontal = false;
    sf::FloatRect collisionOffset{0.f, 0.f, 0.f, 0.f};
    sf::FloatRect collisionBox{0.f, 0.f, 0.f, 0.f};
    bool useCustomCollisionBox = false;

    void updateCollisionBox() {
        if (useCustomCollisionBox) {
            collisionBox.left = position.x + collisionOffset.left;
            collisionBox.top = position.y + collisionOffset.top;
            collisionBox.width = collisionOffset.width;
            collisionBox.height = collisionOffset.height;
        } else {
            collisionBox = sprite.getGlobalBounds();
        }
    }

public:
    Position position;

    Entity(const std::string& imgFile = "", Box box = {}, Position pos = {})
        : position(pos), hitbox(box)
    {
        if (!imgFile.empty()) {
            if (!texture.loadFromFile(imgFile)) {
                std::cerr << "Erro carregando textura: " << imgFile << "\n";
            } else {
                sprite.setTexture(texture);
            }
        }
        sprite.setPosition(position.x, position.y);
        updateCollisionBox();
    }

    void setAnimation(Animation* anim) { animation = anim; }

    void update(float dt = 0) {
        if (!alive) return;
        if (animation) {
            animation->update(dt);
            sprite.setTextureRect(animation->getFrameRect());
        }
        sprite.setPosition(position.x, position.y);
        sprite.setRotation(rotation);
        sprite.setScale(flipHorizontal ? -scaleX : scaleX, scaleY);
        updateCollisionBox();
    }

    void draw(sf::RenderWindow& window) const {
        if (alive) window.draw(sprite);
    }

    bool collide(const Entity& other) const {
        if (!alive || !other.alive) return false;
        return collisionBox.intersects(other.collisionBox);
    }

    void drawCollisionBox(sf::RenderWindow& window, const sf::Color& outline = sf::Color::Red) const {
        sf::RectangleShape r;
        r.setPosition(collisionBox.left, collisionBox.top);
        r.setSize({ collisionBox.width, collisionBox.height });
        r.setFillColor(sf::Color::Transparent);
        r.setOutlineColor(outline);
        r.setOutlineThickness(1.f);
        window.draw(r);
    }

    void destroy() { alive = false; }
    bool isAlive() const { return alive; }

    void setRotation(float angle) { rotation = angle; }
    float getRotation() const { return rotation; }

    void setScale(float sx, float sy) { scaleX = sx; scaleY = sy; }
    std::pair<float,float> getScale() const { return {scaleX, scaleY}; }

    void setFlipHorizontal(bool flip) { flipHorizontal = flip; }
    bool isFlipped() const { return flipHorizontal; }

    sf::Sprite* getSprite() { return &sprite; }
    const sf::Sprite* getSprite() const { return &sprite; }

    Position getPosition() const { return position; }
    void setPosition(const Position& pos) { position = pos; updateCollisionBox(); }
    void moveBy(float dx, float dy) { position.x += dx; position.y += dy; updateCollisionBox(); }

    Box getHitbox() const { return hitbox; }
    void setHitbox(const Box& box) { hitbox = box; }

    sf::FloatRect getGlobalBounds() const { return sprite.getGlobalBounds(); }
    sf::FloatRect getCollisionBox() const { return collisionBox; }

    bool setTextureFromFile(const std::string& imgFile) {
        if (!texture.loadFromFile(imgFile)) return false;
        sprite.setTexture(texture);
        updateCollisionBox();
        return true;
    }

    void setCollisionBox(float offsetX, float offsetY, float width, float height) {
        collisionOffset = sf::FloatRect(offsetX, offsetY, width, height);
        useCustomCollisionBox = true;
        updateCollisionBox();
    }

    void clearCollisionBox() {
        useCustomCollisionBox = false;
        updateCollisionBox();
    }

    bool isUsingCustomCollisionBox() const { return useCustomCollisionBox; }
};

using Object = Entity;

} // namespace Trekka
