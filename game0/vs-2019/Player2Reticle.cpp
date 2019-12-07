#include "Player2Reticle.h"
#include <LogManager.h>
using namespace df;

Player2Reticle::Player2Reticle() {
	setPosition(Vector(38, 33)); //38, 13 + 25
}
//int Player2Reticle::eventHandler(const df::Event* p_e) {
//
//}
Player2Reticle::~Player2Reticle() {

}

void Player2Reticle::kbd(const df::EventKeyboard* p_key_event) {
	switch (p_key_event->getKey()) {
	case df::Keyboard::LEFTARROW:

		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("move reticle with A");
			move(-25);
		}
		break;
	case df::Keyboard::RIGHTARROW:
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




