#include "cmp_missile.h"
#include "maths.h"
#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "cmp_physics.h"
#include "cmp_bullet.h"

void MissileComponent::update(double dt)
{
	auto pl = player.get();

	if (_seeking) {
		//seek behaviour		
	}
	else {
		//dumb behaviour i think this 
	}
}

//void MissileComponent::render() { Renderer::queue(&_sprite.get()->getSprite(), _parent->getView()); }

void MissileComponent::fire() 
{
	auto bullet = _parent->scene->makeEntity();
	auto d = bullet->addComponent<DamageComponent>(_wepSettings.damage);
<<<<<<< HEAD
=======

	auto b = bullet->addComponent<BulletComponent>(d, 5.f);
>>>>>>> 5f00eea67672c79ca92cc531c00b875e25e290df

	auto pS = _parent->GetCompatibleComponent<SpriteComponent>();
	
	auto playerSpriteBounds = pS[0]->getSprite().getPosition();

	_wepHelper._spriteTexture.get()->loadFromFile(_wepHelper.spriteFilename);
	auto s = bullet->addComponent<SpriteComponent>();
	s.get()->loadTexture(_wepHelper, _wepSettings.wepSpriteScale, 0.f);	
	bullet->setPosition(playerSpriteBounds);
	bullet->setView(_parent->getView());

	auto p = bullet->addComponent<PhysicsComponent>(true, s.get()->getSprite().getLocalBounds().getSize());
	p->getBody()->SetBullet(true);
	p->setSensor(true);
	p->setRestitution(_wepSettings.restitution);
	p->setFriction(_wepSettings.friction);
	p->setVelocity(_wepSettings.velocity);
	p->setCategory(_wepSettings.wepCat);

	auto h = bullet->addComponent<HPComponent>(_wepSettings.scene, 100);
	h.get()->setVisible(false);
	p->getBody()->SetUserData(h.get());*/
}

MissileComponent::MissileComponent(Entity* p,textureHelper wepHelper, wepSettings settings) : WeaponComponent(p, settings), _seeking(settings.seeking), _seekRange(settings.range)
{	
	setCategory(settings.wepCat);
	_wepHelper = wepHelper;	
	_wepSettings = settings;		
}

MissileComponent::MissileComponent(Entity* p, wepSettings w) : WeaponComponent(p,w) {}
