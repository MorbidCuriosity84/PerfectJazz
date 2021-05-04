#include "cmp_kamikaze.h"
#include "../movement/cmp_radar.h"
#include "levelManager.h"

//Constructor for kamikaze component.
//Adds two components, missile movement and radar, to the parent enemy component
Kamikaze::Kamikaze(Entity* p, textureSettings enemyTextureHelper, textureSettings bulletTextureHelper, enemySettings enemySettings, weaponSettings weaponSettings, bulletSettings bulletSettings, int index)
	: EnemyComponent(p, enemyTextureHelper, bulletTextureHelper, enemySettings, weaponSettings, bulletSettings, index)
{
	missileCMP = p->addComponent<MissileMovementComponent>(enemySettings.velocity, true, KAMIKAZE);
	auto r = _parent->addComponent<RadarComponent>(8.f, bulletSettings.category);
	r->setRadarFixture();	
	isLoaded = false;
}

//Updates the kamikaze behaviour
void Kamikaze::update(double dt)
{	
	spriteCMP->getSprite().setRotation(_enemySettings.angle);	

	if (_parent->getPosition().y > 0) {
		isLoaded = true;
	}

	//If the kamizake enemy is out to the left or to the right, it's parent is cleared of components, and set not alive
	//the entity is then set off screen, ready to be used again for a new enemy
	if (_parent->getPosition().x > _parent->getView().getSize().x || _parent->getPosition().x < 0 
		|| (isLoaded && _parent->getPosition().x < 0) ) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		physicsCMP->teleport(Vector2f(-500.f, -500.f));
		_parent->clearComponents();
		LevelManager::enemyCount--;
		return;
	}
	EnemyComponent::update(dt);	
}
