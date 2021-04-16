#include "cmp_player.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_weapon.h"


using namespace std;
sf::Clock timer;
sf::Clock bTimer;

void PlayerComponent::Load() {
	wepSettings wS(1.5f, 1, _settings._scene);

	_parent->setPosition(Vector2f(mainView.getSize().x / 2, mainView.getSize().y - 100.f));
	_parent->addComponent<DamageComponent>(_settings._damage);
	_parent->addComponent<WeaponComponent>(wS);
	_parent->addTag("player");
	_spriteHelper.spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);

	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_spriteHelper, _settings._spriteScale, _settings._spriteAngle);
	auto phys = _parent->addComponent<PlayerPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_settings._cat);

	auto h = _parent->addComponent<HPComponent>(_settings._scene, _settings._hp);
	phys.get()->getBody()->SetUserData(h.get());
	_spriteHelper.spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);
	h.get()->setVisible(_settings._hpVisible);
	s.get()->loadTexture(_spriteHelper, _settings._spriteScale, _settings._spriteAngle);

	timer.restart();
}

void PlayerComponent::update(double dt) {

	auto pPhysics = _parent->GetCompatibleComponent<PlayerPhysicsComponent>();
	auto pSprite = _parent->GetCompatibleComponent<SpriteComponent>();

	if (timer.getElapsedTime().asSeconds() > 0.1f) {

		//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
		if (_spriteHelper.spriteRectangle.get()->top == _spriteHelper.spriteTexture.get()->getSize().y / 2) { _spriteHelper.spriteRectangle.get()->top = 0; }
		else { _spriteHelper.spriteRectangle.get()->top = _spriteHelper.spriteTexture.get()->getSize().y / _spriteHelper.spriteRows; }

		//Check if it's loaded the right sprite for the movement
		if (pPhysics[0]->GetDirection() == "right") {
			if (timer.getElapsedTime().asSeconds() > 0.2f) {
				_spriteHelper.spriteRectangle.get()->left = (_spriteHelper.spriteTexture.get()->getSize().x / _spriteHelper.spriteCols) * 4;
			}
			else { _spriteHelper.spriteRectangle.get()->left = (_spriteHelper.spriteTexture.get()->getSize().x / _spriteHelper.spriteCols) * 3; }
		}
		if (pPhysics[0]->GetDirection() == "left") {
			if (timer.getElapsedTime().asSeconds() > 0.2f) {
				_spriteHelper.spriteRectangle.get()->left = (_spriteHelper.spriteTexture.get()->getSize().x / _spriteHelper.spriteCols) * 0;
			}
			else { _spriteHelper.spriteRectangle.get()->left = (_spriteHelper.spriteTexture.get()->getSize().x / _spriteHelper.spriteCols) * 1; }
		}
		if (pPhysics[0]->GetDirection() == "none") {
			_spriteHelper.spriteRectangle.get()->left = (_spriteHelper.spriteTexture.get()->getSize().x / _spriteHelper.spriteCols) * 2;
			timer.restart();
		}
		pSprite[0]->getSprite().setTextureRect(*_spriteHelper.spriteRectangle.get());
	}
}

PlayerComponent::PlayerComponent(Entity* p, textureHelper spriteTexHelp, playerSettings settings)
	: Component(p), _spriteHelper(spriteTexHelp), _settings(settings) {
}
