#include "cmp_hp.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "../game.h"
#include <iostream>
#include "cmp_physics.h"
#include "cmp_damage.h"
#include "../settings/collision_helper.h"

using namespace std;
Texture hpBarTexture;
sf::IntRect hpBarRec;
sf::IntRect overHPBarRec;

void HPComponent::loadHP() {
	underHPBar = _parent->addComponent<SpriteComponent>();
	underHPBar->isFollowingParent(false);
	overHPBar = _parent->addComponent<SpriteComponent>();
	overHPBar->isFollowingParent(false);
	textCMP = _parent->addComponent<TextComponent>(std::to_string(_hp));

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
	textCMP->setFontSize(16u);
}

HPComponent::HPComponent(Entity* const p, Scene* scene, const int hp, const int maxhp)
	: Component(p), _hp(hp), _scene(scene), _visible(true), _maxHp(maxhp), _dynamic(true) {
	parentSpriteCMP = _parent->GetCompatibleComponent<SpriteComponent>()[0];	
}

void HPComponent::handleContact(b2Contact* contact) {
	collisionHelper* compOneHP = static_cast<collisionHelper*>(contact->GetFixtureA()->GetBody()->GetUserData());
	collisionHelper* compTwoHP = static_cast<collisionHelper*>(contact->GetFixtureB()->GetBody()->GetUserData());

	/*cout << "Component One health before collision = " << compOneHP->hpCMP->getHP() << endl;
	cout << "Damage applied = " << compTwoHP->damageCMP->getDamage() << endl;*/
	compTwoHP->damageCMP->applyDamage(compOneHP->hpCMP);
	/*cout << "Component One health after collision = " << compOneHP->hpCMP->getHP() << endl;
	cout << "Damage applied = " << compOneHP->damageCMP->getDamage() << endl;
	cout << "Component Two health before collision = " << compTwoHP->hpCMP->getHP() << endl;*/
	compOneHP->damageCMP->applyDamage(compTwoHP->hpCMP);
	//cout << "Component Two health after collision = " << compTwoHP->hpCMP->getHP() << endl;
}

void HPComponent::setVisible(bool b) {
	_visible = b;
	if (!_visible) {
		/*auto textComp = _parent->GetCompatibleComponent<TextComponent>();
		auto spritComp = _parent->GetCompatibleComponent<SpriteComponent>();*/
		textCMP.get()->setVisible(false);
		overHPBar.get()->setVisible(false);
		underHPBar.get()->setVisible(false);
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
void HPComponent::setHP(int hp_value) { 
	_hp = hp_value;
	if (_hp > _maxHp) {
		_hp = _maxHp;
	}
}
int HPComponent::getHP() { return _hp; }

void HPComponent::setScale(sf::Vector2f scale) {
	//auto s = _parent->GetCompatibleComponent<SpriteComponent>();
	//auto c = _parent->GetCompatibleComponent<TextComponent>();
	underHPBar->getSprite().setScale(scale);
	overHPBar->getSprite().setScale(scale);
}

void HPComponent::update(double dt) {

	_hpText.setString(std::to_string(_hp));

	//auto comp = _parent->GetCompatibleComponent<TextComponent>();
	//auto spr = _parent->GetCompatibleComponent<SpriteComponent>();

	overHPBarRec.left = hpBarTexture.getSize().x * 0;
	overHPBarRec.top = hpBarTexture.getSize().y / 2;
	overHPBarRec.width = hpBarTexture.getSize().x * ((float)_hp / (float)_maxHp);
	overHPBarRec.height = hpBarTexture.getSize().y;
	overHPBar->getSprite().setTextureRect(overHPBarRec);

	if (_dynamic) {
		Vector2f pos = parentSpriteCMP->getSprite().getPosition();

		underHPBar->getSprite().setPosition(Vector2f((round)(pos.x - underHPBar->getSprite().getTextureRect().width / 2), (round)(pos.y - parentSpriteCMP->getSprite().getTextureRect().height / 2 - underHPBar->getSprite().getTextureRect().height)));
		overHPBar->getSprite().setPosition(Vector2f((round)(pos.x - underHPBar->getSprite().getTextureRect().width / 2), (round)(pos.y - parentSpriteCMP->getSprite().getTextureRect().height / 2 - underHPBar->getSprite().getTextureRect().height)));
		textCMP->setPosition(Vector2f((round)(pos.x - (round)(textCMP->getLocalBounds().width / 2)), (round)(pos.y - parentSpriteCMP->getSprite().getTextureRect().height / 2 - underHPBar->getSprite().getTextureRect().height) - textCMP->getGlobalBounds().height + (underHPBar->getSprite().getTextureRect().height / 2 - textCMP->getGlobalBounds().height)));
		textCMP->setText(std::to_string(_hp));
	}
}

void HPComponent::setSpriteColour(sf::Color c) {
	//auto spr = _parent->GetCompatibleComponent<SpriteComponent>();
	overHPBar->getSprite().setColor(c);
}

void HPComponent::setTextColour(sf::Color c) {
	//auto comp = _parent->GetCompatibleComponent<TextComponent>();
	textCMP->_text.setColor(c);
}
void HPComponent::render() {
	if (_visible) {
		Renderer::queue(&_hpText, _parent->getView());
	}
}