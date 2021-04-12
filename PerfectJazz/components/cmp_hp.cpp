#include "cmp_hp.h"
#include "../game.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "cmp_sprite.h"
#include "cmp_text.h"
#include "../scenes/scene_menu.h"
#include "cmp_bullet.h"
#include <iostream>

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

void HPComponent::render() { 
	if (_visible) {
		Renderer::queue(&_hpText, _parent->getView());
	}	
}


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

void HPComponent::setVisible(bool b)
{
	_visible = b;
}

bool HPComponent::isVisible() const
{
	return _visible;
}

HPComponent::HPComponent(Entity* const p, Scene* scene, const int& hp)
	: Component(p), _hp(hp), _scene(scene), _visible(true) {
	loadHP();
}

void HPComponent::handleContact(b2Contact* contact)
{
	/*vector<shared_ptr<BulletComponent>> b = _parent->GetCompatibleComponent<BulletComponent>();
	if (!b.empty()) {		*/
		auto* bullet = static_cast<BulletComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());
		uint16 dam = bullet->getDamage();
		cout << "Bullet damage = " << dam << endl;
		cout << "Player health before collision = " << _hp << endl;
		setHP(_hp - dam);
		cout << "Player health after collision = " << _hp << endl;
		if (_hp < 0)
		{
			_parent->setVisible(false);
			_parent->setAlive(false);
			_parent->setPosition({ -50.f, -50.f });
		}
	//}	
}