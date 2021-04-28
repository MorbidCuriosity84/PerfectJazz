#include "cmp_enemy.h"
#include "ecm.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_enemy_physics.h"
#include "../movement/cmp_movement.h"
#include "../movement/cmp_move_sine.h"
#include "levelManager.h"

using namespace std;
using namespace sf;

void EnemyComponent::Load(int index) {
	vector<Vector2ul> tile = ls::findTiles(_enemySettings.tile);

	_parent->setPosition(Vector2f(ls::getTilePosition(tile[index]).x, ls::getTilePosition(tile[index]).y - Engine::getWindowSize().y/1.5));

	//_parent->addComponent<MovementComponent>(Vector2f(0.f, -50.f));
	_parent->addTag("enemies");
	_enemyTextureHelper.spriteTexture.get()->loadFromFile(_enemyTextureHelper.spriteFilename);
	spriteCMP = _parent->addComponent<SpriteComponent>();
	spriteCMP.get()->loadTexture(_enemyTextureHelper, _enemySettings.scale, _enemySettings.angle);

	damageCMP = _parent->addComponent<DamageComponent>(_enemySettings.damage);
	weaponCMP = _parent->addComponent<WeaponComponent>(_weaponSettings, _bulletSettings, _bulletTextureHelper);

	physicsCMP = _parent->addComponent<EnemyPhysicsComponent>(spriteCMP->getSprite().getGlobalBounds().getSize());
	physicsCMP.get()->setCategory(_enemySettings.category);

	hpCMP = _parent->addComponent<HPComponent>(_enemySettings.scene, _enemySettings.hp, _enemySettings.hp);	
	hpCMP->loadHP();
	hpCMP.get()->setVisible(_enemySettings.hpVisible);
	hpCMP->setSpriteColour(Color::Red);
	hpCMP->setTextColour(Color::White);

	//_parent->addComponent<SineMovementComponent>(Vector2f(0.f,-50.f), 15.f);
}

void EnemyComponent::update(double dt) {	

	_enemyTextureHelper.spriteTimer += dt;

	if (_enemyTextureHelper.spriteTimer < 0.05) {
		_enemyTextureHelper.spriteRectangle.get()->left = (_enemyTextureHelper.spriteTexture.get()->getSize().x / 2) * 0;
	}
	if (_enemyTextureHelper.spriteTimer >= 0.1 && _enemyTextureHelper.spriteTimer < 0.15) {
		_enemyTextureHelper.spriteRectangle.get()->left = (_enemyTextureHelper.spriteTexture.get()->getSize().x / 2) * 1;
	}
	if (_enemyTextureHelper.spriteTimer > 0.2) {
		_enemyTextureHelper.spriteTimer = 0.0;
	}
	spriteCMP->getSprite().setTextureRect(*_enemyTextureHelper.spriteRectangle.get());
	spriteCMP->getSprite().setPosition(_parent->getPosition());
		
	if (_parent->getPosition().y > _parent->getView().getSize().y ||
		_parent->getPosition().y < 0 ||
		_parent->getPosition().x > _parent->getView().getSize().x ||
		_parent->getPosition().x < 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
		LevelManager::enemyCount--;
		cout << "Enemy count " << LevelManager::enemyCount << endl;
	}
	if (hpCMP->getHP() <= 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));

		sounds[_enemySettings.sound].setPitch(1.f + sin(accumulation) * .025f);
		sounds[_enemySettings.sound].setVolume(15.f);
		sounds[_enemySettings.sound].play();
		LevelManager::enemyCount--;
		cout << "Enemy count " << LevelManager::enemyCount << endl;
	}
}

EnemyComponent::EnemyComponent(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: Component(p), _enemyTextureHelper(enemyTextureHelper), _bulletTextureHelper(bulletTextureHelper), _enemySettings(enemySettings), _weaponSettings(weaponSettings), _bulletSettings(bulletSettings), accumulation(0.f) 
{
	Load(index);
	en_colHelp.damageCMP = damageCMP.get();
	en_colHelp.hpCMP = hpCMP.get();
	en_colHelp.isMissile = false;
	en_colHelp.missileCMP = nullptr;

	physicsCMP->getBody()->SetUserData(&en_colHelp);
}





