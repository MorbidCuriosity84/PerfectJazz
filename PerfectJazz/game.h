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
extern Scene* mainScene;
extern sf::View leftView;
extern sf::View rightView;
extern sf::View mainView;
extern shared_ptr<Entity> player;
extern unsigned int gameWidth;
extern unsigned int gameHeight;
static vector<shared_ptr<Entity>> playerBullets;
static vector<shared_ptr<Entity>> enemyBullets;
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
* At least that's my understanding of it. Hopefully it works. There's a switch case of doom further down
* that sets all of these values by switching on a category.
*/
enum _entityCategory {
    BOUNDARY = 0x0001, //1
    PLAYER_BODY = 0x0002, //2
    FRIENDLY_BULLET = 0x0004, //4
    ENEMY_BULLET = 0x0008, //8
    ENEMY_BODY = 0x0010, //16
    FRIENDLY_MISSILE = 0x0020, //32
    ENEMY_MISSILE = 0x0040, //64
    NO_COLLIDE = 0x0080, //128
    ENEMY_MISSILE_RADAR = 0x0100, //256
    FRIENDLY_MISSILE_RADAR = 0x0200, //512
    ENEMY_BODY_RADAR = 0x0400, //1024
    PLAYER_BODY_RADAR = 0x0800, //2048
};

enum _enemyType {
    NONE,
    AIRMAN,
    SERGEANT,
    COLONEL,
};

enum _playerType {
    PLAYER1,
    PLAYER2,
};

enum _bulletType {
    TYPE1,
    TYPE2,
    TYPE3,
};

enum _weaponType {
    GUN,
    MACHINE_GUN,
    ROCKET_LAUNCHER,
};

enum _backgroundType {
    MOUNTAIN,
    MOUNTAIN_OVER,
    FOREST,
    FOREST_OVER,
};

enum _miscType {
    PLAYER_LIFE,
    PLAYER_UPDATE_COUNTER,
};

enum _settingType {
    PLAYER,
    ENEMY,
    WEAPON,
    BULLET,
};

enum _powerUps {
    HP_PWU,
    DAMAGE_PWU,
    FIRERATE_PWU,
    PLAYER_MOVEMENT_PWU,
    BULLET_NUM_PWU,
    COIN_PWU,
};

struct filterGetter {
    filterGetter() {}

    b2Filter getFilter(_entityCategory cat) 
    {
        b2Filter filter;

        //Switch case of doom. This is where we *should* be able to define what collides with what
        switch (cat) {
        case PLAYER_BODY:
            filter.categoryBits = PLAYER_BODY; //belongs to player group
            filter.maskBits = ENEMY_BODY | ENEMY_BULLET | ENEMY_MISSILE | ENEMY_MISSILE_RADAR; //only collides with enemy group
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
            filter.maskBits = ENEMY_BODY | ENEMY_MISSILE;
            break;
        case FRIENDLY_MISSILE:
            filter.categoryBits = FRIENDLY_MISSILE;
            filter.maskBits = ENEMY_BODY | ENEMY_BULLET | ENEMY_MISSILE;
            break;
        case FRIENDLY_MISSILE_RADAR:
            filter.categoryBits = FRIENDLY_MISSILE_RADAR;
            filter.maskBits = ENEMY_BODY;
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
            filter.maskBits = PLAYER_BODY;
            break;
        case NO_COLLIDE:
            filter.groupIndex = -1;
            break;
        default:
            break;
        }
        return filter;
    }
};