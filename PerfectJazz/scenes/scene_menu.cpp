#include "scene_menu.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void MenuScene::Load() {
    cout << "Menu Load \n";
    auto txt = makeEntity();
    auto t = txt->addComponent<TextComponent>("Perfect Jazz v0.002\nPress 1 for Level 1\nPress 2 for Level 2\nPress 3 for Level 3");
    setLoaded(true);
}

void MenuScene::Update(const double& dt) {
    // cout << "Menu Update "<<dt<<"\n";

    if (sf::Keyboard::isKeyPressed(Keyboard::Num1)) {
        Engine::ChangeScene(&level1);
    }

    if (sf::Keyboard::isKeyPressed(Keyboard::Num2)) {
        Engine::ChangeScene(&level2);
    }

    if (sf::Keyboard::isKeyPressed(Keyboard::Num3)) {
        Engine::ChangeScene(&level3);
    }
    Scene::Update(dt);
}
