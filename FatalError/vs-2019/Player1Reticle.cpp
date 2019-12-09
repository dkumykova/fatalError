#include "Player1Reticle.h"
#include <LogManager.h>
#include <DisplayManager.h>
using namespace df;

Player1Reticle::Player1Reticle() {
	setPosition(Vector(38, 14)); //38, 13 + 25
	setSprite("menureticle1");
	selectedString->setSprite("unselected1");
	selectedString->setPosition(Vector(5, 5));

}
//int Player1Reticle::eventHandler(const df::Event* p_e) {
//
//}
//Player1Reticle::~Player1Reticle() {
//
//}
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
	case df::Keyboard::LEFTSHIFT:
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("confirm character for player 1");
			//DM.drawString(Vector(5, 5), "Player 1 has selected", CENTER_JUSTIFIED, RED);
			selectedString->setSprite("selected1");
			selectedString->setPosition(Vector(5, 5));
			//selectedString = PlayerSelected();
			setHighlightedChar(getPosition());
		}
		break;
	case df::Keyboard::LEFTCONTROL:
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("unselect character for player 1");
			selectedString->setSprite("unselected1");
			selectedString->setPosition(Vector(5, 5));
			//DM.drawString(Vector(100, 10), "Player 1 has selected", CENTER_JUSTIFIED, RED);
			setHighlightedChar(Vector());
		}
		break;
	default:
		return;
	};
	return;
}




