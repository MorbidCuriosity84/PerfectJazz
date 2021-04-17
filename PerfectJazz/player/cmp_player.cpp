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
	_parent->setPosition(Vector2f(mainView.getSize().x / 2, mainView.getSize().y - 100.f));
	_parent->addComponent<DamageComponent>(_playerSettings.damage);
	_parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	_parent->addTag("player");
	_playerTextureHelper.spriteTexture.get()->loadFromFile(_playerTextureHelper.spriteFilename);

	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_playerTextureHelper, _playerSettings.scale, _playerSettings.angle);
	auto phys = _parent->addComponent<PlayerPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_playerSettings.category);

	auto h = _parent->addComponent<HPComponent>(_playerSettings.scene, _playerSettings.hp);
	phys.get()->getBody()->SetUserData(h.get());
	_playerTextureHelper.spriteTexture.get()->loadFromFile(_playerTextureHelper.spriteFilename);
	h.get()->setVisible(_playerSettings.hpVisible);
	s.get()->loadTexture(_playerTextureHelper, _playerSettings.scale, _playerSettings.angle);

	timer.restart();
}

void PlayerComponent::update(double dt) {

	auto pPhysics = _parent->GetCompatibleComponent<PlayerPhysicsComponent>();
	auto pSprite = _parent->GetCompatibleComponent<SpriteComponent>();

	if (timer.getElapsedTime().asSeconds() > 0.1f) {

		//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
		if (_playerTextureHelper.spriteRectangle.get()->top == _playerTextureHelper.spriteTexture.get()->getSize().y / 2) { _playerTextureHelper.spriteRectangle.get()->top = 0; }
		else { _playerTextureHelper.spriteRectangle.get()->top = _playerTextureHelper.spriteTexture.get()->getSize().y / _playerTextureHelper.spriteRows; }

		//Check if it's loaded the right sprite for the movement
		if (pPhysics[0]->GetDirection() == "right") {
			if (timer.getElapsedTime().asSeconds() > 0.2f) {
				_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 4;
			}
			else { _playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 3; }
		}
		if (pPhysics[0]->GetDirection() == "left") {
			if (timer.getElapsedTime().asSeconds() > 0.2f) {
				_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 0;
			}
			else { _playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 1; }
		}
		if (pPhysics[0]->GetDirection() == "none") {
			_playerTextureHelper.spriteRectangle.get()->left = (_playerTextureHelper.spriteTexture.get()->getSize().x / _playerTextureHelper.spriteCols) * 2;
			timer.restart();
		}
		pSprite[0]->getSprite().setTextureRect(*_playerTextureHelper.spriteRectangle.get());
	}
}

PlayerComponent::PlayerComponent(Entity* p, textureHelper playerTextureHelper, textureHelper bulletTextureHelper, playerSettings playerSettings, wepSettings weaponSettings, bulletSettings bulletSettings)
	: Component(p), _playerTextureHelper(playerTextureHelper), _bulletTextureHelper(bulletTextureHelper), _playerSettings(playerSettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings) {
}
