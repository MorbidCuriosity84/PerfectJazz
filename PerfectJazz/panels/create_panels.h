#pragma once
#include <ecm.h>
#include "../components/cmp_text.h"
#include "../player/cmp_player.h"

static class Panels {
public:
	static void createPanels(Scene* _scene);
	static void update(double dt);
	void render();
};
