#include "create_player.h"
#include "../game.h"
#include "cmp_player.h"
#include <LevelSystem.h>

using namespace std;
using namespace sf;

void Player::createPlayer(Scene* _scene) {
	auto p = _scene->makeEntity();
	p->setView(mainView);
	playerSettings settings(100, 100000, 0.5f, _scene, .4f, .005f, { 0.f,100.f }, PLAYER, false, { 1.f,1.f }, { 1.f,1.f }, 90.f, 0, FRIENDLY_BULLET);

	auto spriteTexture = make_shared<sf::Texture>();
	auto spriteRectangle = make_shared<sf::IntRect>();
	textureHelper spriteHelp("res/img/player/player_900.png", 2, 5, 0, 2, spriteTexture, spriteRectangle, 1.5);
	auto wepSpriteTexture = make_shared<sf::Texture>();
	auto wepSpriteRectangle = make_shared<sf::IntRect>();
	textureHelper wepHelp("res/img/weapons/Fx_01.png", 1, 3, 0, 2, wepSpriteTexture, wepSpriteRectangle, 2.0);

	auto loadPlayer = p->addComponent<PlayerComponent>(spriteHelp, wepHelp, settings);
	loadPlayer->Load();
}
