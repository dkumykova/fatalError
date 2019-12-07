// The base player chacracter class

// Game Includes
#include "PlayerCharacter.h"
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


using namespace df;
PlayerCharacter::PlayerCharacter() {
	// Move Attributes 
	move_slowdown = 2;
	move_countdown = move_slowdown;
	jump_countdown = 0;

	// Acceleration
	acceleration = Vector(0, 0.5);
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

	my_clock = new Clock();
	
}

PlayerCharacter::~PlayerCharacter() {
	// Mark Reticle for deletion.
	//WM.markForDelete(p_reticle);
}

int PlayerCharacter::eventHandler(const df::Event* p_e){
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

int PlayerCharacter::getHealth() const{
	return health;
}

void PlayerCharacter::attack_1(){

}

void PlayerCharacter::attack_2(){

}

void PlayerCharacter::specialAttack(){

}


void PlayerCharacter::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

	//acceleration.setXY(0, 0.5);
	LM.writeLog("Acceleration: %f, %f", acceleration.getX(), acceleration.getY());
	LM.writeLog("velocity to: %f, %f", getVelocity().getX(), getVelocity().getY());
	Vector new_velocity = Vector(0, getVelocity().getY() + acceleration.getY());

	if (new_velocity.getY() > TERMINAL_VELOCITY) {
		setVelocity(Vector(0, TERMINAL_VELOCITY));
	}
	else {
		setVelocity(Vector(0, getVelocity().getY() + acceleration.getY()));
	}
	// Mimic gravity
	//if (!on_ground) {
		//LM.writeLog("step for jump called");
		//if (jump_countdown < 1) {
			//acceleration += 0.05;
			//setAcceleration(df::Vector(0, acceleration));
			//jump_countdown++;
		//}
		//else {
			//jump_countdown = 0;
		//}
		
	//}

	// Error Check for Height
	if (this->getPosition().getY() > 43.5) {
		LM.writeLog("Height is too high");
		this->setPosition(df::Vector(getPosition().getX(), 43));
	}
}

void PlayerCharacter::move(int dx, int dy) {
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

void PlayerCharacter::mouse(const df::EventMouse* p_mouse_event) {

}

void PlayerCharacter::kbd(const df::EventKeyboard* p_key_event) {
	//LM.writeLog("Acceleration is now: %d", acceleration);
	//long int first_time = my_clock->delta();

	switch (p_key_event->getKey()) {
	case df::Keyboard::W:       // Jump
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("Key down W*");
			long int jump_time = my_clock->split() / 1000;

			if (jump_time < 1000) {
				LM.writeLog("Too quick to jump!");
				LM.writeLog("%ld", jump_time);
				break;
			}
			
			my_clock->delta();
			setVelocity(df::Vector(0, -6));
			LM.writeLog("Setting velocity to: %f, %f", getVelocity().getX(), getVelocity().getY());
			//if (on_ground) {
			//	LM.writeLog("Jump!");
			//	on_ground = false;
			//	//acceleration = -0.6;
			//setAcceleration(df::Vector(0, acceleration));
			//	//setVelocity(df::Vector(0, ));
			//	LM.writeLog("Velocity is now: %d, %d", getVelocity().getX(), getVelocity().getY());
			//	return;
			//}
			//LM.writeLog("Not on ground!");
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

void PlayerCharacter::collide(const df::EventCollision* p_c_event){
	if ((p_c_event->getObject1()->getType() == "Platform") ||
		(p_c_event->getObject2()->getType() == "Platform")) {
		//LM.writeLog("am colliding with platform");
		//if (on_ground)
		//	//return;
		//if (getAcceleration().getY() > 0 && !on_ground) {
		//	on_ground = true;
		//	this->setAcceleration(df::Vector(0, 0));

		//	// Helps eliminate the bug that sometimes it cannot land "on ground", but collide
		//	// I guess this is happening because of collision prediction, or over move.
		//	this->setPosition(df::Vector(getPosition().getX(), 42.5));  
		//}
		setVelocity(df::Vector()); //reset velocity to 0

	}
}
