#include "cmp_hp.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "cmp_sprite.h"
#include "cmp_text.h"

using namespace std;

HPComponent::HPComponent(Entity* const p, const int& hp)
	: Component(p), _hp(hp) {
	loadHP();
}

void HPComponent::update(double dt) {
	auto comp = _parent->GetCompatibleComponent<TextComponent>();
	auto posY = _parent->getPosition().y;
	auto posX = _parent->getPosition().x;
	_hpText.setString(std::to_string(_hp));
	_hpText.setPosition(posX, posY);
}
void HPComponent::render() { Renderer::queue(&_hpText, _parent->getView()); }
void HPComponent::setHP(int hp_value) { _hp = hp_value; }
int HPComponent::getHP() { return _hp; }

void HPComponent::loadHP() {
	auto s = _parent->addComponent<TextComponent>(_hpText.getString());
}
