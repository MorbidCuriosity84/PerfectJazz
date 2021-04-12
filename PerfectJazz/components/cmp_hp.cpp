#include "cmp_hp.h"
#include "../game.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "cmp_sprite.h"
#include "cmp_text.h"
#include "../scenes/scene_menu.h"

using namespace std;
shared_ptr<Entity> overSpriteHP;


void HPComponent::update(double dt) {
	_hpText.setString(std::to_string(_hp));
	auto comp = overSpriteHP->GetCompatibleComponent<TextComponent>();	
	auto spr = _parent->GetCompatibleComponent<SpriteComponent>();
	auto posY = spr[0]->getSprite().getPosition().y - spr[0]->getSprite().getTextureRect().getSize().y;
	auto posX = spr[0]->getSprite().getPosition().x - spr[0]->getSprite().getTextureRect().getSize().x/2;
	comp[0]->setPosition(Vector2f(posX, posY));
	comp[0]->setText(std::to_string(_hp));
	_hp--;
}

void HPComponent::render() { Renderer::queue(&_hpText, _parent->getView()); }


void HPComponent::setHP(int hp_value) { _hp = hp_value; }

int HPComponent::getHP() { return _hp; }

void HPComponent::loadHP() {
	overSpriteHP = _scene->makeEntity();
	overSpriteHP->setView(mainView);
	overSpriteHP->addComponent<TextComponent>(std::to_string(_hp));
	auto comp = overSpriteHP->GetCompatibleComponent<TextComponent>();
	comp[0]->setFontSize(14u);
}

sf::Vector2f HPComponent::getPosition() {
	auto pos = _parent->getPosition();
	return pos;
}

void HPComponent::setPosition(sf::Vector2f position) {
	auto pos = _parent->getPosition();
}

HPComponent::HPComponent(Entity* const p, Scene* scene, const int& hp)
	: Component(p), _hp(hp), _scene(scene) {
	loadHP();
}
