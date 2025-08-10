#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

namespace Trekka {

inline sf::Font& loadSystemFont() {
    static sf::Font font;
    static bool loaded = false;
    if (loaded) return font;

    std::vector<std::string> paths;
#if defined(_WIN32)
    paths = {"C:/Windows/Fonts/arial.ttf", "C:/Windows/Fonts/tahoma.ttf", "C:/Windows/Fonts/calibri.ttf"};
#elif defined(__APPLE__)
    paths = {"/System/Library/Fonts/SFNSDisplay.ttf", "/Library/Fonts/Arial.ttf", "/System/Library/Fonts/Supplemental/Arial.ttf"};
#else
    paths = {"/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", "/usr/share/fonts/truetype/freefont/FreeSans.ttf", "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"};
#endif

    for (auto& p : paths) {
        if (font.loadFromFile(p)) {
            std::cout << "Fonte carregada de: " << p << std::endl;
            loaded = true;
            return font;
        }
    }

    std::cerr << "Nenhuma fonte encontrada, usando padrão SFML.\n";
    loaded = true;
    return font;
}

} // namespace Trekka
