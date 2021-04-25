#pragma once
#include "cmp_player.h"
#include "../components/cmp_weapon.h"
#include "../components/cmp_bullet.h"
#include "../components/cmp_damage.h"
#include "../components/cmp_hp.h"
#include "../settings/player_settings.h"
#include "../settings/weapon_settings.h"
#include "../game.h"


class Player {
public:
	static void createPlayer(Scene* _scene);
};

