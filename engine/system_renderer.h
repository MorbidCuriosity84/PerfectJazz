#pragma once

#include <SFML/Graphics.hpp>
//#include "cmp_sprite.h"

namespace Renderer {
void initialise(sf::RenderWindow&);

void shutdown();

void update(const double&);

void queue(const sf::Drawable* d, const sf::View w);

void map(const sf::Drawable*, sf::View);

void render();
}; // namespace Renderer
