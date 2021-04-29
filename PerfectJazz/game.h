#pragma once
#include "ecm.h"
#include "myContactListener.h"
#include "scenes/scene_title.h"
#include "scenes/scene_level1.h"
#include "scenes/scene_level2.h"
#include "scenes/scene_level3.h"
#include "scenes/scene_main_menu.h"
#include "scenes/scene_menu.h"
#include "scenes/scene_pause_menu.h"
#include "scenes/scene_upgrade_menu.h"
#include "SFML/Audio.hpp"

using namespace std;

extern MenuScene menuScene;
extern MainMenu mainMenuScene;
extern PauseMenu pauseMenu;
extern TitleScene title;
extern Level1Scene level1;
extern Level2Scene level2;
extern Level3Scene level3;
extern UpgradeMenu upgradeMenu;
extern Scene* mainScene;
extern Vector2f windowScale;
extern sf::View leftView;
extern sf::View rightView;
extern sf::View mainView;
extern sf::View menuView;
extern shared_ptr<Entity> player;
extern unsigned int gameWidth;
extern unsigned int gameHeight;
extern myContactListener mContLis;
extern sf::SoundBuffer sBuffs[128];
extern sf::Sound sounds[128];
extern sf::Music musicArray[8];


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
    POWERUP = 0x1000, // 4096
};


//MARK this is to be used with the SOUNDS enum to get the relevant filename for the sound
//this makes it just a case of looping through the array and loading the sound into a buffer 
//that can then be accessed with the enum string
static std::string soundFilenames[32] = {
    "res/sounds/death/sfx_deathscream_human7.wav", //player die 1
    "res/sounds/death/sfx_deathscream_human8.wav", //player die 2
    "res/sounds/death/sfx_deathscream_human12.wav", //player die 3
    "res/sounds/weapons/sfx_wpn_laser7.wav", //bullet fire 1
    "res/sounds/weapons/sfx_wpn_laser9.wav", //bullet fire 2
    "res/sounds/weapons/sfx_wpn_laser11.wav", //bullet fire 3
    "res/sounds/weapons/sfx_wpn_cannon1.wav", //bullet fire 4
    "res/sounds/weapons/sfx_wpn_machinegun_loop2.wav", //bullet fire 5
    "res/sounds/weapons/sfx_wpn_missilelaunch.wav", //missile fire 1
    "res/sounds/weapons/sfx_wpn_cannon2.wav", //missile fire 2
    "res/sounds/weapons/sfx_wpn_cannon4.wav", //missile fire 3
    "res/sounds/weapons/sfx_wpn_cannon6.wav", //missile fire 4
    "res/sounds/impact/sfx_sounds_impact3.wav", //bullet impact 1
    "res/sounds/impact/sfx_sounds_impact3.wav", //bullet impact 2
    "res/sounds/impact/sfx_sounds_impact6.wav", //bullet impact 3
    "res/sounds/impact/sfx_sounds_impact10.wav", //missile impact 1
    "res/sounds/impact/sfx_sounds_impact11.wav", //missile impact 2
    "res/sounds/impact/sfx_sounds_impact14.wav", //missile impact 3
    "res/sounds/death/sfx_deathscream_alien3.wav", //enemy die 1
    "res/sounds/death/sfx_deathscream_alien4.wav", //enemy die 2
    "res/sounds/death/sfx_deathscream_alien5.wav", //enemy die 3
    "res/sounds/death/sfx_deathscream_alien6.wav", //enemy die 4
    "res/sounds/explosions/sfx_exp_short_soft11.wav", //explosion 1
    "res/sounds/explosions/sfx_exp_short_soft12.wav", //explosion 2
    "res/sounds/explosions/sfx_exp_medium4.wav", //explosion 3
    "res/sounds/explosions/sfx_exp_medium11.wav", //explosion 4    
    "res/sounds/explosions/sfx_exp_long4.wav", //explosion 5
    "res/sounds/powerups/sfx_sounds_fanfare1.wav", //powerup 1
    "res/sounds/powerups/sfx_sounds_fanfare2.wav", //powerup 2
    "res/sounds/powerups/sfx_sounds_fanfare3.wav", //powerup 3 
    "res/sounds/powerups/sfx_coin_double1.wav", //powerup 4 coins
    "res/sounds/powerups/sfx_coin_double2.wav", //powerup 5 coins
};

//Easy reference enum to index the sounds
enum SOUNDS {
    PLAYER_DIE_1,
    PLAYER_DIE_2,
    PLAYER_DIE_3,
    BULLET_FIRE_1,
    BULLET_FIRE_2,
    BULLET_FIRE_3,
    BULLET_FIRE_4,
    BULLET_FIRE_5,    
    MISSILE_FIRE_1,
    MISSILE_FIRE_2,
    MISSILE_FIRE_3,
    MISSILE_FIRE_4,    
    BULLET_IMPACT_1,
    BULLET_IMPACT_2,
    BULLET_IMPACT_3,    
    MISSILE_IMPACT_1,
    MISSILE_IMPACT_2,
    MISSILE_IMPACT_3,    
    ENEMY_DIE_1,
    ENEMY_DIE_2,
    ENEMY_DIE_3,
    ENEMY_DIE_4,    
    EXPLOSION_1,
    EXPLOSION_2,
    EXPLOSION_3,
    EXPLOSION_4,
    EXPLOSION_5,
    PICKUP_1,
    PICKUP_2,
    PICKUP_3,
    PICKUP_4, 
    PICKUP_5,
};

//Array of all sounds, access with the MUSIC enum
static std::string musicFiles[8] = {
    "res/sounds/music/01 sawsquarenoise Tittle Screen.ogg",
    "res/sounds/music/Lets Rest.ogg",
    "res/sounds/music/02 sawsquarenoise Stage 1.ogg",
    "res/sounds/music/03 sawsquarenoise Stage 2.ogg",
    "res/sounds/music/04 sawsquarenoise Stage 3.ogg",
    "res/sounds/music/04 sawsquarenoise Stage 3.ogg",
    "res/sounds/music/05 sawsquarenoise Boss Splash.ogg",
    "res/sounds/music/06 sawsquarenoise Boss Theme.ogg",
};

//Easy reference enum to index the music
enum MUSIC {
    MUSIC_TITLE_SCREEN,
    MUSIC_UPGRADE_MENU,
    MUSIC_LEVEL_1,
    MUSIC_LEVEL_2,
    MUSIC_LEVEL_3,
    MUSIC_LEVEL_4,
    MUSIC_LEVEL_5,
    MUSIC_BOSS_SPLASH,
    MUSIC_BOSS_FIGHT,
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

enum _powerUpsType {
    HP_PWU,
    DAMAGE_PWU,
    FIRERATE_PWU,
    PLAYER_MOVEMENT_PWU,
    BULLET_NUM_PWU,
    COIN_PWU,
    ALL_POWERUPS,
};
/*
Enums are boring so if you looked all the way 
down here you deserve a bonus so here's a llama

88 88
88 88
88 88
88 88 ,adPPYYba, 88,dPYba,,adPYba,  ,adPPYYba,
88 88 ""     `Y8 88P'   "88"    "8a ""     `Y8
88 88 ,adPPPPP88 88      88      88 ,adPPPPP88
88 88 88,    ,88 88      88      88 88,    ,88
88 88 `"8bbdP"Y8 88      88      88 `"8bbdP"Y8

       ( \__//)
       .'     )
    __/b d  .  )
   (_Y_`,     .)
    `--'-,-'  )
         (.  )
         (   )
        (   )
       ( . )         .---.
      (    )        (     )
      (   . )      (  .    )
      (      )    (      .  ),
      ( .     `"'`  .       `)\
       (      .              .)\
       ((  .      .   (   .   )\\
       ((       .    (        ) \\
        ((     )     _( .   . )  \\
        ( ( .   )"'"`(.(     )   ( ;
        ( (    )      ( ( . )     \'
         |~(  )        |~(  )
         | ||~|        | ||~|
    jgs  | || |        | || |
        _| || |       _| || |
       /___(| |      /___(| |
          /___(         /___(
*/