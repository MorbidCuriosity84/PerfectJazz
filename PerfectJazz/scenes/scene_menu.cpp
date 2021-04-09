#include "scene_menu.h"
#include "../game.h"
#include "../components/cmp_text.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
using namespace std;
using namespace sf;

void MenuScene::Load() {
    cout << "Menu Load \n";
    std::shared_ptr<sf::View> mainView = make_shared<sf::View>();
    mainView->setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    //views.push_back(mainView);
    auto txt = makeEntity();
    txt->_view = mainView;
    auto t = txt->addComponent<TextComponent>("Perfect Jazz v0.003\nPress 1 for Level 1\nPress 2 for Level 2\nPress 3 for Level 3");
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