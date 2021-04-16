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

	wepSettings wSettings;
	wSettings.damage = 100;
	wSettings.fireTime = 1.5f;
	wSettings.fireTimer = 1.5f;
	wSettings.numBullets = 1;
	wSettings.scene = _playerSettings.scene;
	wSettings.direction = -1.f;

	bulletSettings bSettings;
	bSettings.damage = 100;
	bSettings.hp = 100;
	bSettings.lifetime = 10.f;
	bSettings.scene = _playerSettings.scene;
	bSettings.angle = 90.f;
	bSettings.category = FRIENDLY_BULLET;
	bSettings.direction = 1.f;
	bSettings.velocity = Vector2f(0.f, 100.f);

	_parent->setPosition(Vector2f(mainView.getSize().x / 2, mainView.getSize().y - 100.f));
	_parent->addComponent<DamageComponent>(_playerSettings.damage);
	_parent->addComponent<WeaponComponent>(wSettings, bSettings);
	_parent->addTag("player");
	_spriteHelper.spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);

	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_spriteHelper, _playerSettings.scale, _playerSettings.angle);
	auto phys = _parent->addComponent<PlayerPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_playerSettings.category);

	auto h = _parent->addComponent<HPComponent>(_playerSettings.scene, _playerSettings.hp);
	phys.get()->getBody()->SetUserData(h.get());
	_spriteHelper.spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);
	h.get()->setVisible(_playerSettings.hpVisible);
	s.get()->loadTexture(_spriteHelper, _playerSettings.scale, _playerSettings.angle);

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

PlayerComponent::PlayerComponent(Entity* p, textureHelper spriteTexHelp, playerSettings playerSettings)
	: Component(p), _spriteHelper(spriteTexHelp), _playerSettings(playerSettings) {
}
