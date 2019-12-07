#include "MenuReticle.h"
#include <EventMouse.h>
#include <EventStep.h>
#include <WorldManager.h>
#include <LogManager.h>
using namespace df;

MenuReticle::MenuReticle() {
	move_slowdown = 2;
	move_countdown = move_slowdown;
	setSprite("menureticle");
	setType("MenuReticle");

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);
}

void MenuReticle::kbd(const df::EventKeyboard* p_key_event) {
	/*switch (p_key_event->getKey()) {
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
	return;*/
}
void MenuReticle::move(int dx) {
	//check if it's ok to move
	if (move_countdown > 0) {
		return;
	}
	move_countdown = move_slowdown;

	//if stays in window, allow object to move
	df::Vector new_position(getPosition().getX() + dx, getPosition().getY()); //163 max, 38 min
	if ((new_position.getX() >= 38) && (new_position.getX() <= 163)) {
		WM.moveObject(this, new_position);
	}
	else if (new_position.getX() < 38){
		WM.moveObject(this, Vector(38, getPosition().getY()));
	}
	else if (new_position.getX() > 163) {
		WM.moveObject(this, Vector(163, getPosition().getY()));
	}
}
void MenuReticle::step() {
	//move countdown
	move_countdown--;
	if (move_countdown < 0) {
		move_countdown = 0;
	}

}
int MenuReticle::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_key_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_key_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}
MenuReticle::~MenuReticle() {

}




