#pragma once
#include <ecm.h>
#include <SFML/Graphics/Text.hpp>

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

protected:
	int _hp;
	sf::Vector2f position;
	sf::Text _hpText;
	Scene* _scene;
};

