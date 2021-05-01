#include "cmp_kamikaze.h"
#include "../movement/cmp_radar.h"
#include "levelManager.h"

Kamikaze::Kamikaze(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: EnemyComponent(p, enemyTextureHelper, bulletTextureHelper, enemySettings, weaponSettings, bulletSettings, index)
{
	missileCMP = p->addComponent<MissileMovementComponent>(enemySettings.velocity, true, KAMIKAZE);
	radarCMP = p->addComponent<RadarComponent>(4.f, ENEMY_MISSILE_RADAR);
}

void Kamikaze::update(double dt)
{
	spriteCMP->getSprite().setRotation(_enemySettings.angle);	
	if (_parent->getPosition().x > _parent->getView().getSize().x || _parent->getPosition().x < 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
		_parent->clearComponents();
		cout << "Enemy count before removal kamikaze side = " << LevelManager::enemyCount << endl;
		LevelManager::enemyCount--;
		cout << "Enemy count after removal kamikaze side = " << LevelManager::enemyCount << endl;
		return;
	}
	EnemyComponent::update(dt);	
}
