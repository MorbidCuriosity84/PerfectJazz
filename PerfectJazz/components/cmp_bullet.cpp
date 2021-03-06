#include "cmp_bullet.h"
#include "../movement/cmp_missile_movement.h"
#include "maths.h"
#include <iostream>
#include "cmp_sound.h"
#include "../services/sound_Queue.h"
#include "../movement/cmp_radar.h"

using namespace std;
using namespace sf;

//Adds sprite, damage, physics and hp component to the bullet entity.
void BulletComponent::createBullet() {
	_bulletTextHelper.spriteTexture->loadFromFile(_bulletTextHelper.spriteFilename);
	spriteCMP = _parent->addComponent<SpriteComponent>();

	spriteCMP.get()->loadTexture(_bulletTextHelper, _settings.spriteScale, _settings.angle);	
	//If the bullet category is friendly bullet, sets the colour to yellow and a upsize the sprite
	spriteCMP.get()->getSprite().setRotation(_settings.angle + 180.f);
	if (_settings.category == FRIENDLY_BULLET) {
		spriteCMP->getSprite().setColor(Color::Yellow);
		spriteCMP->getSprite().setScale(Vector2f(1.4f, 1.4f));
	}
	//Sets the damage component to take into consideration the current upgrade count
	damageCMP = _parent->addComponent<DamageComponent>(_settings.damage + (_settings.damage * 0.2 * _settings.damageUpgradeCount));
	physicsCMP = _parent->addComponent<PhysicsComponent>(true, spriteCMP.get()->getSprite().getLocalBounds().getSize());
	
	hpCMP = _parent->addComponent<HPComponent>(_settings.scene, 100, 100);
	hpCMP.get()->loadHP();
	hpCMP.get()->setVisible(false);

	physicsCMP->getBody()->SetBullet(true);
	physicsCMP->setSensor(true);
	Vector2f bulletVelocity = _parent->GetCompatibleComponent<PhysicsComponent>()[0]->getVelocity() + _settings.velocity * _settings.direction;
	physicsCMP->setVelocity(Vector2f(bulletVelocity.x, bulletVelocity.y));
	physicsCMP->setCategory(_settings.category);	

	bulletImpactSound = _settings.sound;	
}

//Updates the bullet sprite and checks the HP and entities position to 
//determine if the entity should be alive or not
void BulletComponent::update(double dt) {
	accumulation += dt;
	_bulletTextHelper.spriteTimer += dt/4;

	//Performs the animation for the sprites by resetting the sprite rectangle
	if (_bulletTextHelper.spriteTimer < 0.01) {
		_bulletTextHelper.spriteRectangle.get()->left = (_bulletTextHelper.spriteTexture.get()->getSize().x / _bulletTextHelper.spriteCols) * 1;
	}
	if (_bulletTextHelper.spriteTimer >= 0.01 && _bulletTextHelper.spriteTimer < 0.03) {
		_bulletTextHelper.spriteRectangle.get()->left = (_bulletTextHelper.spriteTexture.get()->getSize().x / _bulletTextHelper.spriteCols) * 2;
	}
	if (_bulletTextHelper.spriteTimer >= 0.03 && _bulletTextHelper.spriteTimer < 0.04) {
		_bulletTextHelper.spriteRectangle.get()->left = (_bulletTextHelper.spriteTexture.get()->getSize().x / _bulletTextHelper.spriteCols) * 1;
	}
	if (_bulletTextHelper.spriteTimer >= 0.04 && _bulletTextHelper.spriteTimer < 0.05) {
		_bulletTextHelper.spriteRectangle.get()->left = (_bulletTextHelper.spriteTexture.get()->getSize().x / _bulletTextHelper.spriteCols) * 0;
	}
	if (_bulletTextHelper.spriteTimer >= 0.06) {
		_bulletTextHelper.spriteTimer = 0.0;
	}

	spriteCMP->getSprite().setTextureRect(*_bulletTextHelper.spriteRectangle.get());
		
	//If the bullets hp is equal or below 0, sets the bullet to not alive and innactive, and clear the components.
	//Sends the entity off screen so it's ready to be use again by the bullets pool.
	if (hpCMP->getHP() <= 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);	
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
		
		sounds[_settings.sound].setPitch(1.f + sin(accumulation) * .025f);
		sounds[bulletImpactSound].setVolume(15.f);
		sounds[bulletImpactSound].play();
		_parent->clearComponents();		
		return;
	}	
	//If bullets are off screen on the y axis bottom, set the entity to not alive and innactive, and clear the components.
	//Sends the entity off screen so it's ready to be use again by the bullets pool
	if (_parent->getPosition().y > _parent->getView().getSize().y ||
		_parent->getPosition().y < 0 ||
		_parent->getPosition().x > _parent->getView().getSize().x ||
		_parent->getPosition().x < 0) {
		_parent->setAlive(false);
		_parent->setVisible(false);
		physicsCMP->getBody()->SetActive(false);
		physicsCMP->getBody()->SetUserData(nullptr);
		_parent->setPosition(Vector2f(-100.f, -100.f));
		_parent->clearComponents();
	}		
}
//Constructor for bullet component.
//Sets initial values for the collision helper and assigns a body to the player component
BulletComponent::BulletComponent(Entity* p, bulletSettings settings, textureSettings bulletTexHelper)
	: Component(p), _settings(settings), _bulletTextHelper(bulletTexHelper), accumulation(0.f) {
	createBullet();
	bul_colHelp.damageCMP = damageCMP.get();
	bul_colHelp.hpCMP = hpCMP.get();
	bul_colHelp.isMissileRadar = false;
	bul_colHelp.missileCMP = nullptr;
	//If the bullet is a enemy missile or friendly missile, adds a missile movement component
	//and a radard component, and sets the radar fixtures
	if (_settings.category == ENEMY_MISSILE || _settings.category == FRIENDLY_MISSILE) 	{		
		bul_colHelp.missileCMP = p->addComponent<MissileMovementComponent>(Vector2f(0.f, -150.f), false, _settings.category).get();		
		auto r =_parent->addComponent<RadarComponent>(8.f, _settings.category);
		r->setRadarFixture();
		p->addTag("missile");
	}
	physicsCMP->getBody()->SetUserData(&bul_colHelp);
}