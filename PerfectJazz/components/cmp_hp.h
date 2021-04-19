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
	void setScale(sf::Vector2f scale);
	void loadHP();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	bool isVisible() const;
	void handleContact(b2Contact* contact);	
	void setVisible(bool b);
	void setDynamic(bool b);

protected:
	int _hp;
	int _maxHp;
	sf::Vector2f position;
	sf::Text _hpText;
	Scene* _scene;	
	bool _visible;
	bool _dynamic;
};

