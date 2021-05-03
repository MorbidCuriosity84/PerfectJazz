#pragma once
#include "engine.h"
#include "../components/cmp_text.h"

using namespace std;
using namespace sf;

class CreditScene : public Scene
{
protected:
	sf::IntRect _titleRect;
	std::shared_ptr<sf::Texture> _titleText;
	std::shared_ptr<TextComponent> txtCMP;
	double timer;
	int index;
public:
	CreditScene() = default;
	~CreditScene() override = default;
	void Load() override;
	void UnLoad() override;
	void Update(const double& dt) override;
};

