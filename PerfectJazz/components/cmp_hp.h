#pragma once
#include <ecm.h>
#include <SFML/Graphics/Text.hpp>
#include <Box2D/Dynamics/Contacts/b2Contact.h>

class HPComponent : public Component{
public:
	explicit HPComponent(Entity* p, Scene* scene, const int& hp);
	void update(double dt);
	void render();
	void setHP(int hp_value);
	int getHP();
	void loadHP();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	void setVisible(bool b);
	bool isVisible() const;
	void handleContact(b2Contact* contact, HPComponent* compOne, HPComponent* compTwo);
	void collideBullets(HPComponent* compOne, HPComponent* compTwo);
	void collideBulletAndShip(HPComponent* ship, HPComponent* bullet);
	void collideShips(HPComponent* shipOne, HPComponent* shipTwo);

protected:
	int _hp;
	sf::Vector2f position;
	sf::Text _hpText;
	Scene* _scene;	
	bool _visible;
};

