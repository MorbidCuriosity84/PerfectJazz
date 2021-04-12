#pragma once
#include <ecm.h>
#include <SFML/Graphics/Text.hpp>

class HPComponent : public Component{
public:
	explicit HPComponent(Entity* p, const int& hp);
	void update(double dt);
	void render();
	void setHP(int hp_value);
	int getHP();
	void loadHP();

protected:
	int _hp;
	sf::Text _hpText;
};

