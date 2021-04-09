#include "system_renderer.h"
#include <queue>
#include <iostream>

using namespace std;
using namespace sf;

static map<const Drawable*, std::shared_ptr<sf::View>> spriteMap;
static queue<const Drawable*> sprites;
static RenderWindow* rw;

void Renderer::initialise(sf::RenderWindow& r) { rw = &r; }

void Renderer::shutdown() {
  while (!sprites.empty())
    sprites.pop();
}

void Renderer::update(const double&) {}

void Renderer::render() {
  if (rw == nullptr) {
    throw("No render window set! ");
  }
  while (!sprites.empty()) {          
    rw->setView(*spriteMap[sprites.front()]);
    rw->draw(*sprites.front());    
    sprites.pop();
  }
}

void Renderer::map(const sf::Drawable* s, std::shared_ptr<sf::View> v) { spriteMap.insert(make_pair(s, v)); }

void Renderer::queue(const sf::Drawable* s) { sprites.push(s); }