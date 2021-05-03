#pragma once
#include "engine.h"

using namespace sf;
//Level scene, that loads the current level and the player, background, panels and powerups
class LevelScene : public Scene {

public:
	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
	void Render() override;
};