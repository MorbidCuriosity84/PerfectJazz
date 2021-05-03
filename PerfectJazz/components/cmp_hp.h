#pragma once
#include <ecm.h>
#include "engine.h"
#include "../services/myContactListener.h"
#include <SFML/Graphics/Text.hpp>
#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "../components/cmp_sprite.h"
#include "../components/cmp_text.h"

//Health component that will add the necessary sprites and text components
//to create a health bar on top of the entity, that can be switched off.
//It also adds health, that can be used while collision and to set triggers, 
//like death
class HPComponent : public Component {
public:
	std::shared_ptr<SpriteComponent> parentSpriteCMP;
	std::shared_ptr<SpriteComponent> underHPBar;
	std::shared_ptr<SpriteComponent> overHPBar;
	std::shared_ptr<TextComponent> textCMP;			

	virtual void update(double dt) override;
	void setSpriteColour(sf::Color c);
	void setTextColour(sf::Color c);
	void render();
	void setHP(int hp_value);
	void setMaxHP(int hp_value);
	int getMaxHP();
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
	explicit HPComponent(Entity* p, Scene* scene, const int hp, const int maxhp);
	HPComponent() = delete;
protected:
	int _hp;
	int _maxHp;
	sf::Vector2f position;
	sf::Text _hpText;
	Scene* _scene;
	bool _visible;
	bool _dynamic;
	Vector2f spritePos;
	Vector2f underhpPos;
	Vector2f overhpPos;
	sf::FloatRect underhpRect;
	sf::FloatRect overhpRect;
};

