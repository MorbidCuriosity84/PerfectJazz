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
	if (_visible) { //dont decrement bullet hp
		_hp--;
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

void HPComponent::handleContact(b2Contact* contact, HPComponent* compOne, HPComponent* compTwo)
{		

	/*if (compOne->_visible && compTwo->_visible) {
		collideShips(compOne, compTwo);
	}
	if (compOne->_visible && !compTwo->_visible) {
		collideBulletAndShip(compOne, compTwo);
	}
	if (!compOne->_visible && compTwo->_visible) {
		collideBulletAndShip(compTwo, compOne);
	}
	if (!compOne->_visible && !compTwo->_visible) {
		collideBullets(compOne, compTwo);
	}*/

	if (compOne->_visible && !compTwo->_visible) { //is bullet or missile
		vector<shared_ptr<BulletComponent>> bullet = compOne->_parent->GetCompatibleComponent<BulletComponent>();
		uint16 damage = bullet[0].get()->getDamage();
		cout << "Damage = " << damage << endl;
		cout << "Player health before collision = " << compTwo->getHP() << endl;
		compTwo->setHP(compTwo->getHP() - damage);
		cout << "Player health after collision = " << compTwo->getHP() << endl;
	}
	else if (compOne->_visible && compTwo->_visible) {
		collideShips(compOne, compTwo);
		/*vector<shared_ptr<BulletComponent>> bullet = compOne->_parent->GetCompatibleComponent<BulletComponent>();
		uint16 damage = bullet[0].get()->getDamage();
		cout << "Damage = " << damage << endl;
		cout << "Player health before collision = " << compTwo->getHP() << endl;
		compTwo->setHP(compTwo->getHP() - damage);
		cout << "Player health after collision = " << compTwo->getHP() << endl;*/
	}
	else { // is player or enemy
		cout << "Damage to component One = " << compTwo->getHP() << endl;
		cout << "Damage to component Two = " << compOne->getHP() << endl;
		uint16 damageToOne = compTwo->getHP();
		uint16 damageToTwo = compOne->getHP();
		cout << "Component One health before collision = " << compOne->getHP() << endl;
		compTwo->setHP(compOne->getHP() - damageToOne);
		cout << "Component One health after collision = " << compOne->getHP() << endl;
		cout << "Component Two health before collision = " << compTwo->getHP() << endl;
		compTwo->setHP(compTwo->getHP() - damageToTwo);
		cout << "Component Two health after collision = " << compTwo->getHP() << endl;
	}		
}

void HPComponent::collideBullets(HPComponent* compOne, HPComponent* compTwo)
{
	vector<shared_ptr<BulletComponent>> bulletOne = compOne->_parent->GetCompatibleComponent<BulletComponent>();
	vector<shared_ptr<BulletComponent>> bulletTwo = compTwo->_parent->GetCompatibleComponent<BulletComponent>();
	uint16 damageToTwo = bulletOne[0].get()->getDamage();
	uint16 damageToOne = bulletTwo[0].get()->getDamage();
	cout << "Bullet One health before collision = " << compOne->getHP() << endl;
	compTwo->setHP(compOne->getHP() - damageToOne);
	cout << "Bullet One health after collision = " << compOne->getHP() << endl;
	cout << "Bullet Two health before collision = " << compTwo->getHP() << endl;
	compTwo->setHP(compTwo->getHP() - damageToTwo);
	cout << "Bullet Two health after collision = " << compTwo->getHP() << endl;
}

void HPComponent::collideBulletAndShip(HPComponent* ship, HPComponent* bullet)
{
	vector<shared_ptr<BulletComponent>> bulletList = bullet->_parent->GetCompatibleComponent<BulletComponent>();
	uint16 damage = bulletList[0].get()->getDamage();
	cout << "Damage = " << damage << endl;
	cout << "Ship health before collision = " << ship->getHP() << endl;
	ship->setHP(ship->getHP() - damage);
	cout << "Ship health after collision = " << ship->getHP() << endl;
}

void HPComponent::collideShips(HPComponent* compOne, HPComponent* compTwo)
{
	cout << "Damage to Ship One = " << compTwo->getHP() << endl;
	cout << "Damage to Ship Two = " << compOne->getHP() << endl;
	uint16 damageToOne = compTwo->getHP();
	uint16 damageToTwo = compOne->getHP();
	cout << "Ship One health before collision = " << compOne->getHP() << endl;
	compTwo->setHP(compOne->getHP() - damageToOne);
	cout << "Ship One health after collision = " << compOne->getHP() << endl;
	cout << "Ship Two health before collision = " << compTwo->getHP() << endl;
	compTwo->setHP(compTwo->getHP() - damageToTwo);
	cout << "Ship Two health after collision = " << compTwo->getHP() << endl;
}
