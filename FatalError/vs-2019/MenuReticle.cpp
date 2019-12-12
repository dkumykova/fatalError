#include "MenuReticle.h"
#include <EventMouse.h>
#include <EventStep.h>
#include <WorldManager.h>
#include <LogManager.h>
#include "Character_Lisp.h"
#include "Character_Java.h"
#include "Character_Js.h"
#include "Character_C.h"
#include "Character_CPP.h"
#include "Character_Python.h"

using namespace df;

MenuReticle::MenuReticle() {
	move_slowdown = 2;
	move_countdown = move_slowdown;
	//setSprite("menureticle");
	setType("MenuReticle");
	highlightedChar = NULL;

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);

	characterSet = false;
	selectedString = new PlayerSelected();
}

void MenuReticle::kbd(const df::EventKeyboard* p_key_event) {

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
//MenuReticle::~MenuReticle() {
//
//}

void MenuReticle::setHighlightedChar(Vector pos) {
	Vector currentPos = getPosition();
	int x = pos.getX();// currentPos.getX();
	LM.writeLog("Set highlighted char called");
	setCharacterSet(true);
	switch (x)
	{
	case 38:
		highlightedChar = new Character_Lisp();
		break;
	case 63:
		highlightedChar = new Character_Java();
		break;
	case 88:
		//C++
		highlightedChar = new Character_CPP();
		break;
	case 113:
		//python
		highlightedChar = new Character_Python();
		break;
	case 138:
		//C
		highlightedChar = new Character_C();
		break;
	case 163:
		//javascript
		setCharacterSet(false);
		//highlightedChar = new Character_Js();
		return;
		break;
	case 0:
		setCharacterSet(false);
		break;

	default:
		
		break;
	}
	highlightedChar->setActive(false);
}

PlayerCharacter* MenuReticle::getHighlightedChar() const{
	return highlightedChar;
}

void MenuReticle::setCharacterSet(bool isSet) {
	characterSet = isSet;
}
bool MenuReticle::getCharacterSet() const {
	return characterSet;
}




