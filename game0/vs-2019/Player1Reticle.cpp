#include "Player1Reticle.h"
#include <LogManager.h>
using namespace df;

Player1Reticle::Player1Reticle() {
	setPosition(Vector(38, 13)); //38, 13 + 25
}
//int Player1Reticle::eventHandler(const df::Event* p_e) {
//
//}
Player1Reticle::~Player1Reticle() {

}
void Player1Reticle::kbd(const df::EventKeyboard* p_key_event) {
	switch (p_key_event->getKey()) {
	case df::Keyboard::A:

		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("move reticle with A");
			move(-25);
		}
		break;
	case df::Keyboard::D:
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("move reticle with D");
			move(+25);
		}
		break;
	default:
		return;
	};
	return;
}





