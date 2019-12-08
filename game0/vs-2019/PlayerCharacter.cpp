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
#include "EventHealth.h"
#include "Bullet.h"


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
	isPlayer1 = true;
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
	if (p_e->getType() == HEALTH_EVENT) {
		handleHealth();
		return 1;
	}

	// If get here, have ignored this event.
	return 0;
}

void PlayerCharacter::handleHealth() {
	if (!health) {
		return;
	}
	health = health - 20;

	//create health event and send to interested objects
	EventHealth h;
	WM.onEvent(&h);

	if (isPlayer1) {
		df::EventView ev("Player 1 Health:", -20, true);
		WM.onEvent(&ev);
	}
	else {
		df::EventView ev("Player 2 Health:", -20, true);
		WM.onEvent(&ev);
	}
	//send view event with updated health value 

}

int PlayerCharacter::getHealth() const{
	return health;
}

void PlayerCharacter::setIsPlayer1(bool isItTrue) {
	isPlayer1 = isItTrue;
}
bool PlayerCharacter::getIsPlayer1() const {
	return isPlayer1;
}

void PlayerCharacter::attack_1(bool isPlayer1) {
	
	if (isPlayer1) {
		Bullet* p = new Bullet(Vector(getPosition().getX() + 20, getPosition().getY()));
		p->setVelocity(df::Vector(0.2, 0));
	}
	else {
		Bullet* p = new Bullet(Vector(getPosition().getX() - 20, getPosition().getY()));
		p->setVelocity(df::Vector(-0.2, 0));
	}
	
}

void PlayerCharacter::attack_2(bool isPlayer1) {
	//Bullet* p = new Bullet(getPosition());
	if (isPlayer1) {
		Bullet* p = new Bullet(Vector(getPosition().getX() + 20, getPosition().getY()));
		p->setVelocity(df::Vector(2, 0));
	}
	else {
		Bullet* p = new Bullet(Vector(getPosition().getX() - 20, getPosition().getY()));
		p->setVelocity(df::Vector(-2, 0));
	}
	
}


void PlayerCharacter::specialAttack(){

}


void PlayerCharacter::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

	//acceleration.setXY(0, 0.5);
	//LM.writeLog("Acceleration: %f, %f", acceleration.getX(), acceleration.getY());
	//LM.writeLog("velocity to: %f, %f", getVelocity().getX(), getVelocity().getY());
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

}

void PlayerCharacter::collide(const df::EventCollision* p_c_event){
	//if ((p_c_event->getObject1()->getType() == "Platform") ||
	//	(p_c_event->getObject2()->getType() == "Platform")) {

	//	setVelocity(df::Vector()); //reset velocity to 0

	//}
}
