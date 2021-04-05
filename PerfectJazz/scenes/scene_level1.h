#pragma once
#include "engine.h"

using namespace sf;

class Level1Scene : public Scene {

public:
	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
	void Render() override;
};