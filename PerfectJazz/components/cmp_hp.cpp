#include "cmp_hp.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "cmp_text.h"
#include "cmp_sprite.h"
#include "cmp_damage.h"
#include "../game.h"
#include <iostream>
#include "cmp_physics.h"

using namespace std;
Texture hpBarTexture;
sf::IntRect hpBarRec;
sf::IntRect overHPBarRec;

void HPComponent::loadHP() {
	auto underHPBar = _parent->addComponent<SpriteComponent>();
	underHPBar->isFollowingParent(false);
	auto overHPBar = _parent->addComponent<SpriteComponent>();
	overHPBar->isFollowingParent(false);
	auto t = _parent->addComponent<TextComponent>(std::to_string(_hp));

	hpBarTexture.loadFromFile("res/img/others/hp_bar.png");

	hpBarRec.left = (round)(hpBarTexture.getSize().x * 0);
	hpBarRec.top = (round)(hpBarTexture.getSize().y / 2 * 0);
	hpBarRec.width = (round)(hpBarTexture.getSize().x);
	hpBarRec.height = (round)(hpBarTexture.getSize().y / 2);

	overHPBarRec.left = (round)(hpBarTexture.getSize().x * 0);
	overHPBarRec.top = (round)(hpBarTexture.getSize().y / 2);
	overHPBarRec.width = (round)(hpBarTexture.getSize().x);
	overHPBarRec.height = (round)(hpBarTexture.getSize().y / 2);

	underHPBar->getSprite().setTexture(hpBarTexture);
	underHPBar->getSprite().setTextureRect(hpBarRec);
	overHPBar->getSprite().setTexture(hpBarTexture);
	overHPBar->getSprite().setTextureRect(overHPBarRec);
	t->setFontSize(16u);
}

HPComponent::HPComponent(Entity* const p, Scene* scene, const int& hp)
	: Component(p), _hp(hp), _scene(scene), _visible(true), _maxHp(hp), _dynamic(true) {
}

void HPComponent::handleContact(b2Contact* contact) {
	HPComponent* compOneHP = static_cast<HPComponent*>(contact->GetFixtureA()->GetBody()->GetUserData());
	HPComponent* compTwoHP = static_cast<HPComponent*>(contact->GetFixtureB()->GetBody()->GetUserData());
	shared_ptr<DamageComponent> d1 = compOneHP->_parent->GetCompatibleComponent<DamageComponent>()[0];
	shared_ptr<DamageComponent> d2 = compTwoHP->_parent->GetCompatibleComponent<DamageComponent>()[0];

	//cout << "Component One health before collision = " << compOneHP->getHP() << endl;
	//cout << "Damage applied = " << d2.get()->getDamage() << endl;
	d2.get()->applyDamage(compOneHP);
	//cout << "Component One health after collision = " << compOneHP->getHP() << endl;
	//cout << "Damage applied = " << d1.get()->getDamage() << endl;
	//cout << "Component Two health before collision = " << compTwoHP->getHP() << endl;
	d1.get()->applyDamage(compTwoHP);
	//cout << "Component Two health after collision = " << compTwoHP->getHP() << endl;
}

void HPComponent::setVisible(bool b) {
	_visible = b;
	if (!_visible) {
		auto textComp = _parent->GetCompatibleComponent<TextComponent>();
		auto spritComp = _parent->GetCompatibleComponent<SpriteComponent>();
		textComp[0].get()->setVisible(false);
		spritComp[1].get()->setVisible(false);
		spritComp[2].get()->setVisible(false);
	}
}

void HPComponent::setDynamic(bool b) {
	_dynamic = b;
}

bool HPComponent::isDynamic() {
	return _dynamic;
}

sf::Vector2f HPComponent::getPosition() {
	auto pos = _parent->getPosition();
	return pos;
}

void HPComponent::setPosition(sf::Vector2f position) {
	_parent->setPosition(position);
}

bool HPComponent::isVisible() const { return _visible; }
void HPComponent::setHP(int hp_value) { _hp = hp_value; }
int HPComponent::getHP() { return _hp; }

void HPComponent::setScale(sf::Vector2f scale) {
	auto s = _parent->GetCompatibleComponent<SpriteComponent>();
	auto c = _parent->GetCompatibleComponent<TextComponent>();
	s[1]->getSprite().setScale(scale);
	s[2]->getSprite().setScale(scale);
}

void HPComponent::update(double dt) {

	_hpText.setString(std::to_string(_hp));

	auto comp = _parent->GetCompatibleComponent<TextComponent>();
	auto spr = _parent->GetCompatibleComponent<SpriteComponent>();

	overHPBarRec.left = hpBarTexture.getSize().x * 0;
	overHPBarRec.top = hpBarTexture.getSize().y / 2;
	overHPBarRec.width = hpBarTexture.getSize().x * ((float)_hp / (float)_maxHp);
	overHPBarRec.height = hpBarTexture.getSize().y;
	spr[2]->getSprite().setTextureRect(overHPBarRec);

	if (_dynamic) {
		auto pos = spr[0]->getSprite().getPosition();

		spr[1]->getSprite().setPosition(Vector2f((round)(pos.x - spr[1]->getSprite().getTextureRect().width / 2), (round)(pos.y - spr[0]->getSprite().getTextureRect().height / 2 - spr[1]->getSprite().getTextureRect().height)));
		spr[2]->getSprite().setPosition(Vector2f((round)(pos.x - spr[1]->getSprite().getTextureRect().width / 2), (round)(pos.y - spr[0]->getSprite().getTextureRect().height / 2 - spr[1]->getSprite().getTextureRect().height)));
		comp[0]->setPosition(Vector2f((round)(pos.x - (round)(comp[0]->getLocalBounds().width / 2)), (round)(pos.y - spr[0]->getSprite().getTextureRect().height / 2 - spr[1]->getSprite().getTextureRect().height) - comp[0]->getGlobalBounds().height + (spr[1]->getSprite().getTextureRect().height / 2 - comp[0]->getGlobalBounds().height)));
		comp[0]->setText(std::to_string(_hp));
	}
}

void HPComponent::setSpriteColour(sf::Color c) {
	auto spr = _parent->GetCompatibleComponent<SpriteComponent>();
	spr[2]->getSprite().setColor(c);
}

void HPComponent::setTextColour(sf::Color c) {
	auto comp = _parent->GetCompatibleComponent<TextComponent>();
	comp[0]->_text.setColor(c);
}
void HPComponent::render() {
	if (_visible) {
		Renderer::queue(&_hpText, _parent->getView());
	}
}