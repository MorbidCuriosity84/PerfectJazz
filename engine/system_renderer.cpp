#include "system_renderer.h"
#include <queue>
#include <iostream>

using namespace std;
using namespace sf;

static queue<pair<const sf::Drawable*, const sf::View>> sprites;
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
		rw->setView(sprites.front().second);
		rw->draw(*sprites.front().first);
		sprites.pop();
	}
}

void Renderer::queue(const sf::Drawable* d, const sf::View s) {
	//pair<sf::Drawable*, sf::View*> pair (&d, &s);
	pair<const sf::Drawable*, const sf::View> pair = make_pair(d, s);
	sprites.push(pair);
}