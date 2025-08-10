#pragma once
#include <SFML/Graphics.hpp>

namespace Trekka {

struct Position {
    float x = 0.f;
    float y = 0.f;
    Position(float _x = 0.f, float _y = 0.f) : x(_x), y(_y) {}
    bool operator==(const Position& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Position& o) const { return !(*this == o); }
};

struct Box {
    float width = 0.f;
    float height = 0.f;
    Box(float w = 0.f, float h = 0.f) : width(w), height(h) {}
};

struct Geometry {
    int width = 0;
    int height = 0;
    Geometry(int w = 0, int h = 0) : width(w), height(h) {}
};

enum class Key {
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
    Left,Right,Up,Down,
    Space,Escape,Enter,
    Unknown
};

enum class MouseButton {
    Left, Right, Middle, Unknown
};

} // namespace Trekka
