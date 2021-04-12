#pragma once

#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_menu.h"
#include "ecm.h"
#include "myContactListener.h"

using namespace std;

extern MenuScene menu;
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;
extern sf::View leftView;
extern sf::View rightView;
extern sf::View mainView;
extern unsigned int gameWidth;
extern unsigned int gameHeight;
extern std::shared_ptr<Entity> player;
extern myContactListener mContLis;


/*
* //I thought this would be a good way to specify a group that an entity belongs to 
* This should make bullet collisions easy to handle. b2d has this filter component for every body
* with categorybits that determine what a body belongs to and maskbits for what it collides with
* I think this should give us some flexibility by allowing us to have objects only collide with certain others.
* 
* https://www.iforce2d.net/b2dtut/collision-filtering <-- this is a good explanation
* 
* So if you want player to collide with enemy bullets and enemy missiles you would set 
* 
* player_body.filter.categorybits = PLAYERS
* player_body.filter.categorybits = ENEMY | ENEMY_MISSiLE | ENEMY_BULLET
* 
* This works because it essentially performs a bitwise AND to check the collision 
* At least that's my understanding of it. Hopefully it works. There's a switch case of doom in the physics component
* that sets all of these values by switching on a category.
*/
enum _entityCategory {
    BOUNDARY = 0x0001,
    PLAYER = 0x0002,
    FRIENDLY_BULLET = 0x0004,
    ENEMY_BULLET = 0x0008,
    ENEMY = 0x0010,
    FRIENDLY_MISSILE = 0x0020,
    ENEMY_MISSILE = 0x0040,
};