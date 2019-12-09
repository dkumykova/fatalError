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
#include "DisplayManager.h"

PlayerChracter::PlayerChracter() {
	// Move Attributes 
	move_slowdown = 2;
	move_countdown = move_slowdown;

	// Acceleration
	acceleration = 0.5;
	on_ground = false;

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
	df::Vector position(WM.getView().getHorizontal() / 2, WM.getBoundary().getVertical() / 2);
	setPosition(position);
	
	// Set Altitude
	setAltitude(3);
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

	// Mimic gravity
	if (!on_ground) {
		acceleration += 0.05;
		setAcceleration(df::Vector(0, acceleration));
	}

	// Error Check for Height
	if (this->getPosition().getY() > 43.5) {
		this->setPosition(df::Vector(getPosition().getX(), 43));
	}
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
	case df::Keyboard::W:       // Jump
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			if (on_ground) {
				on_ground = false;
				acceleration = -0.6;
				setAcceleration(df::Vector(0, acceleration));
				return;
			}
		}
		break;
	case df::Keyboard::A:       // Left
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			move(-1, 0);
			return;
		}
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
		if (on_ground)
			return;
		if (getAcceleration().getY() > 0 && !on_ground) {
			on_ground = true;
			this->setAcceleration(df::Vector(0, 0));

			// Helps eliminate the bug that sometimes it cannot land "on ground", but collide
			// I guess this is happening because of collision prediction, or over move.
			this->setPosition(df::Vector(getPosition().getX(), 42.5));  
		}

	}
}
