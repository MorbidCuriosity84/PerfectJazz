#include "cmp_physics.h"
#include "system_physics.h"

using namespace std;
using namespace sf;
using namespace Physics;

// Updates the physics component
void PhysicsComponent::update(double dt) {
	timer += dt;
	// Sets the position and rotation en relation to the body
	if (timer < 0.1) {
		_parent->setPosition(invert_height(bv2_to_sv2(_body->GetPosition())));
		_parent->setRotation((180 / b2_pi) * _body->GetAngle());
		timer = 0;
	}
}
// Constructor for the physics component
// Defines the body that is used for collisions
PhysicsComponent::PhysicsComponent(Entity* p, bool dyn,
	const Vector2f& size)
	: Component(p), _dynamic(dyn) {

	b2BodyDef BodyDef;
	// Is Dynamic(moving), or static(Stationary)
	BodyDef.type = _dynamic ? b2_dynamicBody : b2_staticBody;
	BodyDef.position = sv2_to_bv2(invert_height(p->getPosition()));

	// Create the body
	_body = Physics::GetWorld()->CreateBody(&BodyDef);
	_body->SetActive(true);
	{
		// Create the fixture shape
		b2PolygonShape Shape;
		// SetAsBox box takes HALF-Widths!
		Shape.SetAsBox(sv2_to_bv2(size).x * 0.5f, sv2_to_bv2(size).y * 0.5f);
		b2FixtureDef FixtureDef;
		// Fixture properties
		// FixtureDef.density = _dynamic ? 10.f : 0.f;
		FixtureDef.friction = _dynamic ? 0.1f : 0.8f;
		FixtureDef.restitution = .2;
		FixtureDef.shape = &Shape;
		// Add to body
		_fixture = _body->CreateFixture(&FixtureDef);
		FixtureDef.restitution = .2;
	}
	timer = 0;
}
// Teleports the body to a new position
void PhysicsComponent::teleport(const sf::Vector2f& v) {
	_body->SetTransform(sv2_to_bv2(invert_height(v)), 0.0f);
}

// Sets the state of the sensor
void PhysicsComponent::setSensor(bool b) {
	_fixture->SetSensor(b);
}

void PhysicsComponent::setCategory(_entityCategory cat) {
	b2Filter filter;

	//  Switch case of doom. This is where we *should* be able to define what collides with what. 
	//  When adding a new enemy make sure to add their category to the weapon catgories mask or you wont be able to shoot them down =)
	switch (cat) {
	case PLAYER_BODY:
		filter.categoryBits = PLAYER_BODY; // belongs to player group
		filter.maskBits = ENEMY_BODY | ENEMY_BULLET | ENEMY_MISSILE | POWERUP | ENEMY_MISSILE_RADAR | KAMIKAZE | BESERKER; //only collides with enemy group
		break;
	case ENEMY_BODY:
		filter.categoryBits = ENEMY_BODY;
		filter.maskBits = PLAYER_BODY | ENEMY_BODY | FRIENDLY_BULLET | FRIENDLY_MISSILE | FRIENDLY_MISSILE_RADAR;
		break;
	case ENEMY_BULLET:
		filter.categoryBits = ENEMY_BULLET;
		filter.maskBits = PLAYER_BODY | FRIENDLY_MISSILE;
		break;
	case ENEMY_MISSILE:
		filter.categoryBits = ENEMY_MISSILE;
		filter.maskBits = PLAYER_BODY | FRIENDLY_BULLET | FRIENDLY_MISSILE;
		break;
	case FRIENDLY_BULLET:
		filter.categoryBits = FRIENDLY_BULLET;
		filter.maskBits = ENEMY_BODY | ENEMY_MISSILE | KAMIKAZE | BESERKER;
		break;
	case FRIENDLY_MISSILE:
		filter.categoryBits = FRIENDLY_MISSILE;
		filter.maskBits = ENEMY_BODY | ENEMY_BULLET | ENEMY_MISSILE | KAMIKAZE | BESERKER;
		break;
	case FRIENDLY_MISSILE_RADAR:
		filter.categoryBits = FRIENDLY_MISSILE_RADAR;
		filter.maskBits = ENEMY_BODY | KAMIKAZE | BESERKER;
		break;
	case ENEMY_MISSILE_RADAR:
		filter.categoryBits = ENEMY_MISSILE_RADAR;
		filter.maskBits = PLAYER_BODY;
		break;
	case PLAYER_BODY_RADAR:
		filter.categoryBits = PLAYER_BODY_RADAR;
		filter.maskBits = ENEMY_BODY;
		break;
	case ENEMY_BODY_RADAR:
		filter.categoryBits = ENEMY_BODY_RADAR;
		filter.maskBits = PLAYER_BODY | FRIENDLY_MISSILE;
		break;
	case POWERUP:
		filter.categoryBits = POWERUP;
		filter.maskBits = PLAYER_BODY;
		break;
	case KAMIKAZE:
		filter.categoryBits = KAMIKAZE;
		filter.maskBits = PLAYER_BODY | FRIENDLY_BULLET | FRIENDLY_MISSILE | FRIENDLY_MISSILE_RADAR;
	case BESERKER:
		filter.categoryBits = BESERKER;
		filter.maskBits = PLAYER_BODY | FRIENDLY_BULLET | FRIENDLY_MISSILE | FRIENDLY_MISSILE_RADAR;
	case NO_COLLIDE:
		filter.groupIndex = -1;
		break;
	default:
		break;
	}
	_fixture->SetFilterData(filter);
}

// Gets the linear velocity of the body
const sf::Vector2f PhysicsComponent::getVelocity() const {
	return bv2_to_sv2(_body->GetLinearVelocity(), true);
}
// Sets the linear velocity of the body
void PhysicsComponent::setVelocity(const sf::Vector2f& v) {
	_body->SetLinearVelocity(sv2_to_bv2(v, true));
}
// Gets the body fixture
b2Fixture* const PhysicsComponent::getFixture() const { return _fixture; }

// Gets the body
b2Body* PhysicsComponent::getBody() { return _body; }

// Deconstructor for the physics component
PhysicsComponent::~PhysicsComponent() {
	auto a = Physics::GetWorld();
	_body->SetActive(false);
	Physics::GetWorld()->DestroyBody(_body);
	_body = nullptr;
}

// Renders the physics component to....nothing? :D
void PhysicsComponent::render() {}

// Sets the impulse for the body's movement
void PhysicsComponent::impulse(const sf::Vector2f& i) {
	auto a = b2Vec2(i.x, i.y * -1.0f);
	_body->ApplyLinearImpulseToCenter(a, true);
	if (_parent->is_fordeletion()) {
		_body->SetActive(false);
	}
}
// Sets the dampen value for the body's movement
void PhysicsComponent::dampen(const sf::Vector2f& i) {
	auto vel = _body->GetLinearVelocity();
	vel.x *= i.x;
	vel.y *= i.y;
	_body->SetLinearVelocity(vel);
}