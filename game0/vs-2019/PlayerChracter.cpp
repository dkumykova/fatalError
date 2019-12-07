// The base player chacracter class

// Game Includes
#include "PlayerChracter.h"
#include "Hero.h"
#include "GameOver.h"

// Event Includes
#include "EventStep.h"
#include "EventView.h"

// Manager Includes
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"

PlayerChracter::PlayerChracter() {
	// Move Attributes 
	move_slowdown = 2;
	move_countdown = move_slowdown;

	// Acceleration
	acceleration = 0;

	// Hit Point
	health = 100;

	//listen for keyboard events
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	//registerInterest(df::MSE_EVENT);

	//create reticle
	//p_reticle = new Reticle();
	//p_reticle->draw();

	// Set Type
	setType("PlayerCharacter");

	// Set Starting Position
	df::Vector position(7, WM.getBoundary().getVertical() / 2);
	setPosition(position);
	setSolidness(df::HARD);
}

PlayerChracter::~PlayerChracter() {
	// Mark Reticle for deletion.
	//WM.markForDelete(p_reticle);
}

int PlayerChracter::eventHandler(const df::Event* p_e){
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_coll_event = dynamic_cast <const df::EventCollision*> (p_e);
		collide(p_coll_event);
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

int PlayerChracter::getHealth() const{
	return health;
}

void PlayerChracter::attack_1(){

}

void PlayerChracter::attack_2(){

}

void PlayerChracter::specialAttack(){

}


void PlayerChracter::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

	if (acceleration < 2)
		acceleration += 0.3;
}

void PlayerChracter::move(int dx, int dy) {
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;
	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical()))
		WM.moveObject(this, new_pos);
}

void PlayerChracter::mouse(const df::EventMouse* p_mouse_event) {

}

void PlayerChracter::kbd(const df::EventKeyboard* p_key_event) {
	
	switch (p_key_event->getKey()) {
	case df::Keyboard::W:       // Up
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			//if (acceleration == 0)
			//acceleration = -10;
			setAcceleration(df::Vector(0, 1));
		}
		break;
	case df::Keyboard::A:       // Left
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			move(-1, 0);
		break;
	case df::Keyboard::S:       // Defend
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			//
		break;
	case df::Keyboard::D:       // Right
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			move(1, 0);
		break;

	case df::Keyboard::ESCAPE:  // quit
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			new GameOver;
		break;
	default: // Key not handled.
		return;
	};

	return;
}

void PlayerChracter::collide(const df::EventCollision* p_c_event){
	if ((p_c_event->getObject1()->getType() == "Platform") ||
		(p_c_event->getObject2()->getType() == "Platform")) {
		LM.writeLog("collide!");
		if (getAcceleration().getY() != 0)
			this->setAcceleration(df::Vector(0, 0));
	}
}
