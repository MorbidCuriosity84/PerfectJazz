#include "cmp_background_physics.h"
#include "system_physics.h"
#include <LevelSystem.h>
#include <SFML/Window/Keyboard.hpp>

using namespace std;
using namespace sf;
using namespace Physics;

//Updates the position of the background using a constant velocity value
//to create the effect of scrolling down
void BackgroundPhysicsComponent::update(double dt) {
	const auto pos = _parent->getPosition();
	_parent->setPosition(Vector2f(pos.x, pos.y + (float)dt * _Velocity.y));
}

//Sets the velocity of the background entity
void BackgroundPhysicsComponent::setVelocity(sf::Vector2f velocity) { _Velocity = velocity; }
//Gets the velocity of the background entity
sf::Vector2f BackgroundPhysicsComponent::getVelocity() { return _Velocity; }

//Background physics component constructor, that sets the body to false, so it doesn't interact
//with other entities
BackgroundPhysicsComponent::BackgroundPhysicsComponent(Entity* p,
	const Vector2f& size)
	: PhysicsComponent(p, true, size) {
	_size = sv2_to_bv2(size, true);
	_body->SetActive(false);
}