#include "create_panels.h"
#include "create_panels.h"
#include "../components/cmp_text.h"
#include "../game.h"

void Panels::createPanels(Scene* _scene) {

	//Left Panel
	{
		auto txt = _scene->makeEntity();
		txt->setView(leftView);
		auto t = txt->addComponent<TextComponent>("This is the left view");
		t->setFontSize(18u);
	}

	//Right Panel
	{
		auto txt2 = _scene->makeEntity();
		txt2->setView(rightView);
		auto t2 = txt2->addComponent<TextComponent>("This is the right view");
		t2->setFontSize(18u);
	}
}
