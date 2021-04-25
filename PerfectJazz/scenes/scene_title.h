#pragma once
#include "engine.h"
#include "../components/cmp_text.h"

class TitleScene : public Scene{
public:
	TitleScene() = default;
	~TitleScene() override = default;

	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
protected:
	double timer;
	std::shared_ptr<TextComponent> txtCMP;
};

