#include "cmp_enemy.h"
#include "ecm.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../movement/cmp_movement.h"
#include "../movement/cmp_move_sine.h"
#include "levelManager.h"
#include <random>
#include "../services/detecting_keys.h"
#include "../player/cmp_player.h"
#include "../services/randomNumber.h"

using namespace std;
using namespace sf;

void EnemyComponent::Load(int index) {

	if (_enemySettings.category == ENEMY_BODY) {
		vector<Vector2ul> tile = ls::findTiles(_enemySettings.tile);
		_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x, ls::getTilePosition(tile[index]).y - Engine::getWindowSize().y));
	}
	else {
		float xPos = RandomNumber::generateUniformRealNumber(0.0, mainView.getSize().x);
		_parent->setPosition(Vector2f(xPos, -50.f));
	}
	_parent->addTag("enemies");
	_enemyTextureHelper.spriteTexture.get()->loadFromFile(_enemyTextureHelper.spriteFilename);
	spriteCMP = _parent->addComponent<SpriteComponent>();
	spriteCMP.get()->loadTexture(_enemyTextureHelper, _enemySettings.scale, _enemySettings.angle);
	damageCMP = _parent->addComponent<DamageComponent>(_enemySettings.damage);
	if (_enemySettings.category != KAMIKAZE) {
		_weaponSettings.fireTimer = RandomNumber::generateUniformRealNumber(0.0, _weaponSettings.fireTime);
		weaponCMP = _parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	}
	physicsCMP = _parent->addComponent<EnemyPhysicsComponent>(spriteCMP->getSprite().getGlobalBounds().getSize());
	physicsCMP.get()->setCategory(_enemySettings.category);

	hpCMP = _parent->addComponent<HPComponent>(_enemySettings.scene, _enemySettings.hp, _enemySettings.hp);
	hpCMP->loadHP();
	//Set currentHP to the acutal HP
	currentHP = hpCMP->getHP();
	hpCMP.get()->setVisible(_enemySettings.hpVisible);
	hpCMP->setSpriteColour(Color::Red);
	hpCMP->setTextColour(Color::White);

	//_parent->addComponent<MovementComponent>(_enemySettings.velocity);	
}

void EnemyComponent::update(double dt) {

	_enemyTextureHelper.spriteTimer += dt;
	if (_enemySettings.type == AIRMAN || _enemySettings.type == SERGEANT || _enemySettings.type == COLONEL) {
		if (_enemyTextureHelper.spriteTimer < 0.05) {
			_enemyTextureHelper.spriteRectangle.get()->left = (_enemyTextureHelper.spriteTexture.get()->getSize().x / 2) * 0;
		}
		if (_enemyTextureHelper.spriteTimer >= 0.1 && _enemyTextureHelper.spriteTimer < 0.15) {
			_enemyTextureHelper.spriteRectangle.get()->left = (_enemyTextureHelper.spriteTexture.get()->getSize().x / 2) * 1;
		}
		if (_enemyTextureHelper.spriteTimer > 0.2) {
			_enemyTextureHelper.spriteTimer = 0.0;
		}
	}
	spriteCMP->getSprite().setTextureRect(*_enemyTextureHelper.spriteRectangle.get());
	spriteCMP->getSprite().setPosition(_parent->getPosition());
	spriteCMP->getSprite().setRotation(_parent->getRotation() + _enemySettings.angle);


	if (_parent->getPosition().y > _parent->getView().getSize().y) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
		auto type = _parent->GetCompatibleComponent<EnemyComponent>()[0].get()->_enemySettings.type;
		_parent->clearComponents();
		LevelManager::enemyCount--;
		return;

	}

	if (hpCMP->getHP() <= 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));

		auto type = _parent->GetCompatibleComponent<EnemyComponent>()[0].get()->_enemySettings.type;
		if (type == AIRMAN) { player->GetCompatibleComponent<PlayerComponent>()[0].get()->_playerSettings.score += 10; }
		if (type == SERGEANT) { player->GetCompatibleComponent<PlayerComponent>()[0].get()->_playerSettings.score += 20; }
		if (type == COLONEL) { player->GetCompatibleComponent<PlayerComponent>()[0].get()->_playerSettings.score += 30; }
		if (type == BANSAI) { player->GetCompatibleComponent<PlayerComponent>()[0].get()->_playerSettings.score += 40; }
		if (type == MADMAN) { player->GetCompatibleComponent<PlayerComponent>()[0].get()->_playerSettings.score += 50; }
		sounds[_enemySettings.sound].setPitch(1.f + sin(accumulation) * .025f);
		sounds[_enemySettings.sound].setVolume(35.f);
		sounds[_enemySettings.sound].play();
		_parent->clearComponents();
		LevelManager::enemyCount--;
		if (type == AIRMAN || type == COLONEL || type == SERGEANT) {
			Scene::deadEnemies++;
		}
	}
}

EnemyComponent::EnemyComponent(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: Component(p), _enemyTextureHelper(enemyTextureHelper), _bulletTextureHelper(bulletTextureHelper), _enemySettings(enemySettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings), accumulation(0.f) {
	Load(index);
	en_colHelp.damageCMP = damageCMP.get();
	en_colHelp.hpCMP = hpCMP.get();
	en_colHelp.isMissileRadar = false;
	en_colHelp.missileCMP = nullptr;

	physicsCMP->getBody()->SetUserData(&en_colHelp);
}





