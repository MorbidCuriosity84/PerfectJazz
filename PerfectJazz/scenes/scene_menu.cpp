#include "scene_menu.h"
#include "../game.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void MenuScene::Load() {
    cout << "Menu Load \n";

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
    Scene::Update(dt);
}
