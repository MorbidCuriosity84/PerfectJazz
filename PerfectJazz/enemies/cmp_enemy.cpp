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

//Loads the enemies, adding the necessary components to it and assigning initial values 
// for the position, hp, and damage
void EnemyComponent::Load(int index) {
	//If the enemy category is enemy body, it gets set its position according to the wave file
	if (_enemySettings.category == ENEMY_BODY) {
		vector<Vector2ul> tile = ls::findTiles(_enemySettings.tile);
		_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x, ls::getTilePosition(tile[index]).y - Engine::getWindowSize().y));
	}
	//If not, its set off screen, ready to come into the screen, with a random x position
	else {
		float xPos = RandomNumber::generateUniformRealNumber(0.0, mainView.getSize().x);
		_parent->setPosition(Vector2f(xPos, -100.f));
	}
	_parent->addTag("enemies");
	_enemyTextureHelper.spriteTexture.get()->loadFromFile(_enemyTextureHelper.spriteFilename);
	spriteCMP = _parent->addComponent<SpriteComponent>();
	spriteCMP.get()->loadTexture(_enemyTextureHelper, _enemySettings.scale, _enemySettings.angle);

	damageCMP = _parent->addComponent<DamageComponent>(_enemySettings.damage);
	//If the enemy is of type kamikaze, gives a random fire rate between the actual and 0,
	//and adds a weapon component to it
	if (_enemySettings.category != KAMIKAZE) {
		_weaponSettings.fireTimer = RandomNumber::generateUniformRealNumber(0.0, _weaponSettings.fireTime);
		weaponCMP = _parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);
	}
	physicsCMP = _parent->addComponent<EnemyPhysicsComponent>(spriteCMP->getSprite().getGlobalBounds().getSize());
	physicsCMP.get()->setCategory(_enemySettings.category);

	hpCMP = _parent->addComponent<HPComponent>(_enemySettings.scene, _enemySettings.hp, _enemySettings.hp);
	hpCMP->loadHP();
	//Sets currentHP to the acutal HP
	currentHP = hpCMP->getHP();
	hpCMP.get()->setVisible(_enemySettings.hpVisible);
	hpCMP->setSpriteColour(Color::Red);
	hpCMP->setTextColour(Color::White);
}

//Updates the component sprite, to perform an animation
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
	//Sets the new texture according to the new rectangle position and updates the position and rotation
	spriteCMP->getSprite().setTextureRect(*_enemyTextureHelper.spriteRectangle.get());
	spriteCMP->getSprite().setPosition(_parent->getPosition());
	//spriteCMP->getSprite().setRotation(_parent->getRotation() + _enemySettings.angle);

	//If enemy off screen on the y axis bottom, set the entity to not alive and innactive, and clear the components.
	//Sends the entity off screen so it's ready to be use again by the enemy pool
	if (_parent->getPosition().y > _parent->getView().getSize().y) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		physicsCMP->teleport(Vector2f(-500.f, -500.f));
		auto type = _parent->GetCompatibleComponent<EnemyComponent>()[0].get()->_enemySettings.type;
		_parent->clearComponents();
		LevelManager::enemyCount--;
		return;

	}
	//If the enemy hp is equal or below 0, sets the enemy to not alive and innactive, and clear the components.
	//Sends the entity off screen so it's ready to be use again by the enemy pool.
	if (hpCMP->getHP() <= 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		physicsCMP->teleport(Vector2f(-500.f, -500.f));

		//Gets the enemycomponent from the parent, and adds to the player score depending on the type of enemy
		auto type = _parent->GetCompatibleComponent<EnemyComponent>()[0].get()->_enemySettings.type;
		int score;
		if (type == AIRMAN) { score = 100; }
		if (type == SERGEANT) { score = 200; }
		if (type == COLONEL) { score = 300; }
		if (type == BANSAI) { score = 400; }
		if (type == MADMAN) { score = 500; }

		player->GetCompatibleComponent<PlayerComponent>()[0].get()->_playerSettings.score += score;
		//Plays a sound on enemy death
		sounds[_enemySettings.sound].setPitch(1.f + sin(accumulation) * .025f);
		sounds[_enemySettings.sound].setVolume(35.f);
		sounds[_enemySettings.sound].play();
		_parent->clearComponents();
		//Lowers enemy count
		LevelManager::enemyCount--;
		//If the enemy is of the type airman, colonel or sergean, increases the enemy count
		if (type == AIRMAN || type == COLONEL || type == SERGEANT) {
			Scene::deadEnemies++;
		}
	}
}
//Constructor for enemy component.
//Sets initial values for the collision helper and assigns a body to the player component
EnemyComponent::EnemyComponent(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: Component(p), _enemyTextureHelper(enemyTextureHelper), _bulletTextureHelper(bulletTextureHelper), _enemySettings(enemySettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings), accumulation(0.f) {
	Load(index);
	en_colHelp.damageCMP = damageCMP.get();
	en_colHelp.hpCMP = hpCMP.get();
	en_colHelp.isMissileRadar = false;
	en_colHelp.missileCMP = nullptr;

	physicsCMP->getBody()->SetUserData(&en_colHelp);
}





