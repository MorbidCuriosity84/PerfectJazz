#include "cmp_player.h"
#include "../game.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_player_physics.h"
#include "../components/cmp_hp.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_bullet.h"


using namespace std;
sf::Clock timer;
sf::Texture playerTexture;
sf::IntRect playerRectangle;

void PlayerComponent::fire() {
	auto bullet = _parent->scene->makeEntity();
	auto pSpr = _parent->GetCompatibleComponent<SpriteComponent>();
	_weaponSpriteHelper._spriteTexture.get()->loadFromFile(_weaponSpriteHelper.spriteFilename);
	auto s = bullet->addComponent<SpriteComponent>();
	s->loadTexture(_weaponSpriteHelper, _settings._wepSpriteScale, _settings._wepAngle);
	bullet->setPosition({ _parent->getPosition().x, _parent->getPosition().y - pSpr[0]->getSprite().getTextureRect().height/2});
	auto d = bullet->addComponent<DamageComponent>(_settings._damage);
	auto b = bullet->addComponent<BulletComponent>(d, 5.f);
	bullet->setView(_parent->getView());


	auto p = bullet->addComponent<PhysicsComponent>(true, s.get()->getSprite().getLocalBounds().getSize());
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(_settings._restitution);
	p->setFriction(_settings._friction);
	p->setVelocity(_settings._velocity);
	p->setCategory(_settings._wepCat);

	auto h = bullet->addComponent<HPComponent>(_settings._scene, 100);	
	h.get()->setVisible(_settings._hpVisible);
	p->getBody()->SetUserData(h.get());
}

void PlayerComponent::Load() {
	_spriteHelper._spriteTexture.get()->loadFromFile(_spriteHelper.spriteFilename);
	auto s = _parent->addComponent<SpriteComponent>();
	s.get()->loadTexture(_spriteHelper, _settings._spriteScale, _settings._spriteAngle);

	_parent->setPosition(Vector2f(mainView.getSize().x / 2, mainView.getSize().y - 100.f));
	auto phys = _parent->addComponent<PlayerPhysicsComponent>(s->getSprite().getGlobalBounds().getSize());
	phys.get()->setCategory(_settings._cat);
	auto h = _parent->addComponent<HPComponent>(_settings._scene, _settings._hp);
	auto d = _parent->addComponent<DamageComponent>(_settings._damage);
	h.get()->setVisible(true);
	phys->getBody()->SetUserData(h.get());	
	_parent->addTag("player");
	timer.restart();
}

void PlayerComponent::update(double dt) {

	auto pPhysics = _parent->GetCompatibleComponent<PlayerPhysicsComponent>();
	auto pSprite = _parent->GetCompatibleComponent<SpriteComponent>();

	if (timer.getElapsedTime().asSeconds() > 0.1f) {

		//Check if the loaded sprite is the bottom, if so, load the top. And viceversa
		if (_spriteHelper._spriteRectangle.get()->top == _spriteHelper._spriteTexture.get()->getSize().y / 2) { _spriteHelper._spriteRectangle.get()->top = 0; }
		else { _spriteHelper._spriteRectangle.get()->top = _spriteHelper._spriteTexture.get()->getSize().y / 2; }

		//Check if it's loaded the right sprite for the movement
		if (pPhysics[0]->GetDirection() == "right") {
			if (timer.getElapsedTime().asSeconds() > 0.2f) {
				_spriteHelper._spriteRectangle.get()->left = (_spriteHelper._spriteTexture.get()->getSize().x / 5) * 4;
			}
			else { _spriteHelper._spriteRectangle.get()->left = (_spriteHelper._spriteTexture.get()->getSize().x / 5) * 3; }
		}
		if (pPhysics[0]->GetDirection() == "left") {
			if (timer.getElapsedTime().asSeconds() > 0.2f) {
				_spriteHelper._spriteRectangle.get()->left = (_spriteHelper._spriteTexture.get()->getSize().x / 5) * 0;
			}
			else { _spriteHelper._spriteRectangle.get()->left = (_spriteHelper._spriteTexture.get()->getSize().x / 5) * 1; }
		}
		if (pPhysics[0]->GetDirection() == "none") {
			_spriteHelper._spriteRectangle.get()->left = (_spriteHelper._spriteTexture.get()->getSize().x / 5) * 2;
			timer.restart();
		}
		pSprite[0]->getSprite().setTextureRect(*_spriteHelper._spriteRectangle.get());
	}

	_fireTime -= dt;
	if (_fireTime <= 0.f) {
		fire();
		_fireTime = _settings._fireTime;
	}
	static float angle = 0.f;
	angle += 1.f * dt;
}

PlayerComponent::PlayerComponent(Entity* p, textureHelper spriteTexHelp, textureHelper wepSpriteTexHelp, playerSettings settings)
	: Component(p), _spriteHelper(spriteTexHelp), _weaponSpriteHelper(wepSpriteTexHelp), _settings(settings) {
}


