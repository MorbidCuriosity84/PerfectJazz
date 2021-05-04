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

// Loads the hp, by adding sprites and text components to its entity.
// It will display a bar with the current hp and a text with the values. This can be toggled offf
void HPComponent::loadHP() {
	underHPBar = _parent->addComponent<SpriteComponent>();
	underHPBar->isFollowingParent(false);
	overHPBar = _parent->addComponent<SpriteComponent>();
	overHPBar->isFollowingParent(false);
	textCMP = _parent->addComponent<TextComponent>(std::to_string(_hp));

	hpBarTexture.loadFromFile("res/img/others/hp_bar.png");

	setScale(Vector2f(1.2f, 1.2f));
	// Settings for each of the sprites rectangles, to get the right sprite from the sprite sheet
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

	// Sets the font size and sets the origin in the middle of the text component
	textCMP->setFontSize(20u);
	textCMP->setOrigin(Vector2f((round)(textCMP->getGlobalBounds().width / 2), (round)(textCMP->getGlobalBounds().height / 2)));

	spritePos = parentSpriteCMP->getSprite().getPosition();
	overhpRect = overHPBar->getSprite().getLocalBounds();
	underhpRect = underHPBar->getSprite().getLocalBounds();
	underHPBar->getSprite().setOrigin((round)(underhpRect.width / 2), (round)(underhpRect.height / 2));
	overHPBar->getSprite().setOrigin((round)(overHPBarRec.width / 2), (round)(overHPBarRec.height / 2));
}
// Constructor for the hp component
// Creates a reference to the parents sprite component
HPComponent::HPComponent(Entity* const p, Scene* scene, const int hp, const int maxhp)
	: Component(p), _hp(hp), _scene(scene), _visible(true), _maxHp(maxhp), _dynamic(true) {
	parentSpriteCMP = _parent->GetCompatibleComponent<SpriteComponent>()[0];
}
// Handles the contacts between hp entities, applying damage when they collide
void HPComponent::handleContact(b2Contact* contact) {
	collisionHelper* compOneHP = static_cast<collisionHelper*>(contact->GetFixtureA()->GetBody()->GetUserData());
	collisionHelper* compTwoHP = static_cast<collisionHelper*>(contact->GetFixtureB()->GetBody()->GetUserData());

	compTwoHP->damageCMP->applyDamage(compOneHP->hpCMP);
	compOneHP->damageCMP->applyDamage(compTwoHP->hpCMP);
}

// Sets the visibility of the hp component
void HPComponent::setVisible(bool b) {
	_visible = b;
	if (!_visible) {
		textCMP.get()->setVisible(false);
		overHPBar.get()->setVisible(false);
		underHPBar.get()->setVisible(false);
	}
}
// Sets the dynamic to false or true
void HPComponent::setDynamic(bool b) {
	_dynamic = b;
}
// Checks if the hp component is dynamic
bool HPComponent::isDynamic() {
	return _dynamic;
}
// Gets the position of the hp component
sf::Vector2f HPComponent::getPosition() {
	auto pos = _parent->getPosition();
	return pos;
}
// Sets the position of the hp component
void HPComponent::setPosition(sf::Vector2f position) {
	_parent->setPosition(position);
}

// Checks if the hp component is visible
bool HPComponent::isVisible() const { return _visible; }
// Sets the hp of the hp component
void HPComponent::setHP(int hp_value) {
	_hp = hp_value;
	if (_hp > _maxHp) {
		_hp = _maxHp;
	}
}
// Sets the max hp of the hp component
void HPComponent::setMaxHP(int hp_value) {
	_maxHp = hp_value;
	if (_maxHp > 999999) {
		_maxHp = 999999;
	}
}
// Gets the max hp of the hp component
int HPComponent::getMaxHP() {
	return _maxHp;
}
int HPComponent::getHP() { return _hp; }

// Sets the scale of the hp component sprites
void HPComponent::setScale(sf::Vector2f scale) {
	underHPBar->getSprite().setScale(scale * windowScale);
	overHPBar->getSprite().setScale(scale * windowScale);
}
// Updates the hp component, performing animation for the hp bar
// so increases or decreases with the hp value
void HPComponent::update(double dt) {

	_hpText.setString(std::to_string(_hp));

	overHPBarRec.left = hpBarTexture.getSize().x * 0;
	overHPBarRec.top = hpBarTexture.getSize().y / 2;
	overHPBarRec.width = (round)(hpBarTexture.getSize().x * ((float)_hp / (float)_maxHp));
	overHPBarRec.height = hpBarTexture.getSize().y;
	overHPBar->getSprite().setTextureRect(overHPBarRec);

	// If the hp component is dynamic, sets the sprites and text to it's parent's position
	if (_dynamic) {
		Vector2f pos = _parent->getPosition();

		underHPBar->getSprite().setPosition(Vector2f((round)(pos.x), (round)(pos.y - parentSpriteCMP->getSprite().getGlobalBounds().height / 2 - underHPBar->getSprite().getGlobalBounds().height / 2)));
		overHPBar->getSprite().setPosition(Vector2f((round)(pos.x), (round)(pos.y - parentSpriteCMP->getSprite().getGlobalBounds().height / 2 - underHPBar->getSprite().getGlobalBounds().height / 2)));
		textCMP->setText(std::to_string(_hp));
		textCMP->setOrigin(Vector2f((round)(textCMP->getGlobalBounds().width / 2), (round)(textCMP->getGlobalBounds().height / 2)));
		textCMP->setPosition(Vector2f((round)(pos.x), (round)(overHPBar->getSprite().getPosition().y - textCMP->getLocalBounds().top)));
	}
}
// Sets the sprite colour of the hp component
void HPComponent::setSpriteColour(sf::Color c) {
	overHPBar->getSprite().setColor(c);
}
// Sets the text colour of the hp component
void HPComponent::setTextColour(sf::Color c) {
	textCMP->_text.setColor(c);
}
// Renders the hp component, adding it to the renderer queue
void HPComponent::render() {
	if (_visible) {
		Renderer::queue(&_hpText, _parent->getView());
	}
}