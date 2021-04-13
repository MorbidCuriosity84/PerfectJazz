#include "cmp_hp.h"
#include "../game.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "cmp_sprite.h"
#include "cmp_text.h"
#include "../scenes/scene_menu.h"
#include "cmp_bullet.h"
#include <iostream>
#include "cmp_player_physics.h"

using namespace std;
shared_ptr<Entity> overSpriteHP;


void HPComponent::update(double dt) {
	_hpText.setString(std::to_string(_hp));
	auto comp = _parent->GetCompatibleComponent<TextComponent>();	
	auto spr = _parent->GetCompatibleComponent<SpriteComponent>();
	auto posY = spr[0]->getSprite().getPosition().y - spr[0]->getSprite().getTextureRect().getSize().y;
	auto posX = spr[0]->getSprite().getPosition().x - spr[0]->getSprite().getTextureRect().getSize().x/2;
	comp[0]->setPosition(Vector2f(posX, posY));
	comp[0]->setText(std::to_string(_hp));	

	if (_hp < 0) {
		_parent->setForDelete();
	}
}

void HPComponent::render() { 
	if (_visible) {
		Renderer::queue(&_hpText, _parent->getView());
	}	
}


void HPComponent::setHP(int hp_value) { _hp = hp_value; }

int HPComponent::getHP() { return _hp; }

void HPComponent::loadHP() {	
	auto t = _parent->addComponent<TextComponent>(std::to_string(_hp));
	t->setFontSize(14u);

	/*overSpriteHP = _scene->makeEntity();
	overSpriteHP->setView(mainView);
	overSpriteHP->addComponent<TextComponent>(std::to_string(_hp));
	auto comp = overSpriteHP->GetCompatibleComponent<TextComponent>();
	comp[0]->setFontSize(14u);*/
}

sf::Vector2f HPComponent::getPosition() {
	auto pos = _parent->getPosition();
	return pos;
}

void HPComponent::setPosition(sf::Vector2f position) {
	auto pos = _parent->getPosition();
}

void HPComponent::setVisible(bool b) { _visible = b; }

bool HPComponent::isVisible() const { return _visible; }

HPComponent::HPComponent(Entity* const p, Scene* scene, const int& hp)
	: Component(p), _hp(hp), _scene(scene), _visible(true) {
	loadHP();
}

void HPComponent::handleContact(b2Contact* contact)
{		
	HPComponent* compOneHP = static_cast<HPComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
	HPComponent* compTwoHP = static_cast<HPComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());
	shared_ptr<DamageComponent> d1 = compOneHP->_parent->GetCompatibleComponent<DamageComponent>()[0];
	shared_ptr<DamageComponent> d2 = compTwoHP->_parent->GetCompatibleComponent<DamageComponent>()[0];

	cout << "Component One health before collision = " << compOneHP->getHP() << endl;
	cout << "Damage applied = " << d2.get()->getDamage() << endl;
	d2.get()->applyDamage(compOneHP);
	cout << "Component One health after collision = " << compOneHP->getHP() << endl;
	cout << "Damage applied = " << d1.get()->getDamage() << endl;
	cout << "Component Two health before collision = " << compTwoHP->getHP() << endl;
	d1.get()->applyDamage(compTwoHP);
	cout << "Component Two health after collision = " << compTwoHP->getHP() << endl;
}
