#pragma once
#include <ecm.h>
#include "engine.h"
#include "../myContactListener.h"
#include <SFML/Graphics/Text.hpp>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "ecm.h"
#include "engine.h"

class HPComponent : public Component {
public:
	virtual void update(double dt) override;
	void setSpriteColour(sf::Color c);
	void setTextColour(sf::Color c);
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
	bool isDynamic();
	explicit HPComponent(Entity* p, Scene* scene, const int& hp);
	HPComponent() = delete;
protected:
	int _hp;
	int _maxHp;
	sf::Vector2f position;
	sf::Text _hpText;
	Scene* _scene;
	bool _visible;
	bool _dynamic;
};

