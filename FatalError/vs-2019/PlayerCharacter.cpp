// The base player chacracter class

// Game Includes
#include "PlayerCharacter.h"
#include "GameOver.h"
#include "Player.h"

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

// PlayerCharacter Constructor
// Initialize:
// 1. Move related: (Character Dependent)
// move_slowdown, move_countdown, jump_countdown, acceleration (falling speed), on_ground
// 2. 
PlayerCharacter::PlayerCharacter() {

	// Move Attributes 
	move_slowdown = 2;
	move_countdown = move_slowdown;
	jump_countdown = 0;
	on_ground = false;

	// Acceleration
	acceleration = Vector(0, 0.5);

	//listen for keyboard events
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	//registerInterest(df::MSE_EVENT);

	// Set Type
	setType("PlayerCharacter");

	// Set Starting Position
	df::Vector position(WM.getView().getHorizontal() / 2, WM.getBoundary().getVertical() / 2);
	setPosition(position);
	
	// Set Altitude
	setAltitude(3);

	// Set Attack Damage
	setAttackOneDamage(10); // If not specifically defined, then it's 10
	setAttackTwoDamage(20); // If not specifically defined, then it's 20
}

PlayerCharacter::~PlayerCharacter() {
	// Mark Reticle for deletion.
	//WM.markForDelete(p_reticle);
	

}

void PlayerCharacter::moveRight(){
	// No implementation because this is player dependent
}

void PlayerCharacter::moveLeft(){
	// No implementation because this is player dependent
}

void PlayerCharacter::jump(){
	// No implementation because this is player dependent
}

int PlayerCharacter::eventHandler(const df::Event* p_e){
	
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




void PlayerCharacter::attack_1() {
	// No implementation because this is player dependent
}

void PlayerCharacter::attack_2() {
	// No implementation because this is player dependent
}

void PlayerCharacter::specialAttack(){
	// No implementation because this is player dependent
}

void PlayerCharacter::setAttackOneDamage(int damage){
	m_attack_1_damage = damage;
}

int PlayerCharacter::getAttackOneDamage() const{
	return m_attack_1_damage;
}

void PlayerCharacter::setAttackTwoDamage(int damage){
	m_attack_2_damage = damage;
}

int PlayerCharacter::getAttackTwoDamage() const{
	return m_attack_2_damage;
}


void PlayerCharacter::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;

	Vector new_velocity = Vector( (getVelocity().getX() + acceleration.getX()) , 
								  (getVelocity().getY() + acceleration.getY()));

	// Check for Velocity, Cap it
	if (new_velocity.getX() > TERMINAL_VELOCITY_X && new_velocity.getY() > TERMINAL_VELOCITY_Y ) {
		setVelocity(Vector(TERMINAL_VELOCITY_X, TERMINAL_VELOCITY_Y));
	}
	else if (new_velocity.getX() > TERMINAL_VELOCITY_X) {
		setVelocity(Vector(TERMINAL_VELOCITY_X, getVelocity().getY() + acceleration.getY()));
	}
	else if (new_velocity.getY() > TERMINAL_VELOCITY_Y){
		setVelocity(Vector(getVelocity().getX() + acceleration.getX(), TERMINAL_VELOCITY_Y));
	}
	else {
		setVelocity(Vector(getVelocity().getX() + acceleration.getX(), getVelocity().getY() + acceleration.getY()));
	}

	// Error Check for Height
	if (this->getPosition().getY() > 43.5) {
		LM.writeLog("Height is too Low");
		this->setPosition(df::Vector(getPosition().getX(), 43));
	}

	stepProcessor();
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



// Process General Collisions
void PlayerCharacter::collide(const df::EventCollision* p_c_event){
	
	// Helps Only Process when Player Is Not On Ground
	if (!on_ground) {
		if ((p_c_event->getObject1()->getType() == "Platform") ||
			(p_c_event->getObject2()->getType() == "Platform")) {

			on_ground = true;
			setVelocity(df::Vector()); //reset velocity to 0

		}
	}
	
	// Call Character Specific Collision Processor
	processCollision();
}

void PlayerCharacter::processCollision(){
	// No implementation because this is player dependent
}

void PlayerCharacter::stepProcessor(){
	// No implementation because this is player dependent
}

void PlayerCharacter::setCharacterAcceleration(Vector new_a) {
	acceleration = new_a;
}

void PlayerCharacter::swapOnGroundStatus(){
	on_ground = !on_ground;
}

void PlayerCharacter::setPlayer(Player* n_player){
	m_p_player = n_player;
	this->setPosition(n_player->getPosition());
}

Player* PlayerCharacter::getPlayer() const {
	return m_p_player;
}