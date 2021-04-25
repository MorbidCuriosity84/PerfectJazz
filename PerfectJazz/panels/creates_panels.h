#pragma once
#include <ecm.h>
#include "../components/cmp_text.h"
#include "../components/cmp_sprite.h"
#include "../components/cmp_hp.h"
#include "../game.h"

class Panels {
public:
	static void createPanels(Scene* _scene);
	static void update(double dt);
	static void setLifeSprites();
	static void createUpgradeSprites();
	static void setUpgradesSprites(string type, int counter);

	Panels() = default;
	~Panels();
	void render();
};