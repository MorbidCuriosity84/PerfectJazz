#pragma once
#include <ecm.h>
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_hp.h"
#include "../player/cmp_player.h"
#include "../game.h"
#include "../player/create_player.h"

class Panels {
public:
	static void createPanels(Scene* _scene);
	static void update(double dt);
	static void setLifeSprites();
	void render();
};
