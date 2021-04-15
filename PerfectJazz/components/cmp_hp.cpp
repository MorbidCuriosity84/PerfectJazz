#include "cmp_hp.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "cmp_sprite.h"
#include "cmp_text.h"
#include "cmp_bullet.h"
#include "cmp_player_physics.h"
#include "../game.h"
#include "../scenes/scene_menu.h"
#include <iostream>

using namespace std;
Texture hpBarTexture;
sf::IntRect hpBarRec;
sf::IntRect overHPBarRec;

void HPComponent::update(double dt) {

	_hpText.setString(std::to_string(_hp));

	auto comp = _parent->GetCompatibleComponent<TextComponent>();
	auto spr = _parent->GetCompatibleComponent<SpriteComponent>();

	comp[0]->setText(std::to_string(_hp));

	auto entitySpriteBounds = spr[0]->getSprite().getTextureRect().getSize();
	auto hpSpriteBounds = spr[1]->getSprite().getTextureRect().getSize();
	auto textBounds = comp[0]->getLocalBounds();

	comp[0]->setOrigin(Vector2f((floor)((textBounds.width - hpSpriteBounds.x)/2), (textBounds.height + entitySpriteBounds.y/2)));
	spr[1]->getSprite().setOrigin(Vector2f((floor)((hpSpriteBounds.x + entitySpriteBounds.x)/2), (textBounds.height + entitySpriteBounds.y/2)));
	spr[2]->getSprite().setOrigin(Vector2f((floor)((hpSpriteBounds.x + entitySpriteBounds.x)/2), (textBounds.height + entitySpriteBounds.y/2)));

	auto pos = spr[0]->getSprite().getPosition();

	comp[0]->setPosition(pos);
	spr[1]->getSprite().setPosition(pos);
	spr[2]->getSprite().setPosition(pos);

	overHPBarRec.left = hpBarTexture.getSize().x * 0;
	overHPBarRec.top = hpBarTexture.getSize().y / 2;
	overHPBarRec.width = hpBarTexture.getSize().x * ((float)_hp / (float)_maxHp);
	overHPBarRec.height = hpBarTexture.getSize().y / 2;
	spr[2]->getSprite().setTextureRect(overHPBarRec);


	if (_hp <= 0) {
		_parent->setForDelete();
	}
}

void HPComponent::render() {
	if (_visible) {
		Renderer::queue(&_hpText, _parent->getView());
	}
}


void HPComponent::loadHP() {
	auto t = _parent->addComponent<TextComponent>(std::to_string(_hp));
	auto underHPBar = _parent->addComponent<SpriteComponent>();
	auto overHPBar = _parent->addComponent<SpriteComponent>();

	hpBarTexture.loadFromFile("res/img/others/hp_bar.png");

	hpBarRec.left = hpBarTexture.getSize().x * 0;
	hpBarRec.top = hpBarTexture.getSize().y / 2 * 0;
	hpBarRec.width = hpBarTexture.getSize().x;
	hpBarRec.height = hpBarTexture.getSize().y / 2;

	overHPBarRec.left = hpBarTexture.getSize().x * 0;
	overHPBarRec.top = hpBarTexture.getSize().y / 2;
	overHPBarRec.width = hpBarTexture.getSize().x;
	overHPBarRec.height = hpBarTexture.getSize().y / 2;

	underHPBar->getSprite().setTexture(hpBarTexture);
	underHPBar->getSprite().setTextureRect(hpBarRec);
	overHPBar->getSprite().setTexture(hpBarTexture);
	overHPBar->getSprite().setTextureRect(overHPBarRec);

	t->setFontSize(12u);
}

HPComponent::HPComponent(Entity* const p, Scene* scene, const int& hp)
	: Component(p), _hp(hp), _scene(scene), _visible(true) {
	_maxHp = _hp;
	loadHP();
}

void HPComponent::handleContact(b2Contact* contact) {
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

sf::Vector2f HPComponent::getPosition() {
	auto pos = _parent->getPosition();
	return pos;
}

void HPComponent::setPosition(sf::Vector2f position) {
	auto comp = _parent->GetCompatibleComponent<TextComponent>();
	comp[0]->setPosition(position);
}

void HPComponent::setVisible(bool b) {
	_visible = b;
	//CARLOS - We should be able to not draw this???
	if (!_visible) {
		auto textComp = _parent->GetCompatibleComponent<TextComponent>();
		auto spritComp = _parent->GetCompatibleComponent<SpriteComponent>();
		textComp[0].get()->setVisible(false);		
		spritComp[1].get()->setVisible(false);
		spritComp[2].get()->setVisible(false);
	}
}

bool HPComponent::isVisible() const { return _visible; }
void HPComponent::setHP(int hp_value) { _hp = hp_value; }
int HPComponent::getHP() { return _hp; }