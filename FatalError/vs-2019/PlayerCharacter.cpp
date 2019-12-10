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
#include <EventOut.h>


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

void PlayerCharacter::setErrorAttacking(bool status) {
	m_error_attacking = status;
}

bool PlayerCharacter::getErrorAttacking() const {
	return m_error_attacking;
}

void PlayerCharacter::startSuperChanneling(){
	if (super_channeling_slowdown == 0) { // which means no cd for super
		super_attack_countdown = m_super_cast_time * 30 + super_attack_slowdown;
		m_super_attacking = true;
		do_action_super_attack();
		return;
	}

	// Else start channeling
	m_super_channeling = true;
}

bool PlayerCharacter::isTimeToJump(){
	if (jump_countdown > 0 || !on_ground)
		return false;
	
	jump_countdown = jump_slowdown;
	return true;
}

bool PlayerCharacter::isTimeToHorizontalMove(){
	if (horizontal_move_countdown > 0)
		return false;

	horizontal_move_countdown = horizontal_move_slowdown;
	return true;
}

bool PlayerCharacter::isTimeToDefense(){
	if (defense_countdown > 0)
		return false;

	defense_countdown = defense_slowdown;
	return true;
}

bool PlayerCharacter::isTimeToAttackOne(){
	if (attack_1_countdown > 0)
		return false;
	
	attack_1_countdown = attack_1_slowdown;
	return true;
}

bool PlayerCharacter::isTimeToAttackTwo(){
	if (attack_2_countdown > 0 || getErrorAttacking())
		return false;

	return true;
}

bool PlayerCharacter::isTimeToSuperAttack(){
	if (super_attack_countdown > 0 || m_super_attacking)
		return false;

	return true;
}

void PlayerCharacter::getFrozen(int time){
	int actual_slowdown_time = time * 30; // 30 steps per second
	
	horizontal_move_countdown = actual_slowdown_time;
	jump_countdown = actual_slowdown_time;
	attack_1_countdown = actual_slowdown_time;
	attack_2_countdown = actual_slowdown_time;
	super_attack_countdown = actual_slowdown_time;
	defense_countdown = actual_slowdown_time;
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
	//handle if character goes out of bounds of box
	/*if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}*/

	// if get super attack end event, then check for caster. If caster is this character, reset counter to slowdown
	// Also remember to turn super_attacking back to false
	// To do

	// If get here, have ignored this event.
	return 0;
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
	int halfWidth = getAnimation().getSprite()->getWidth() / 2;
	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);
	
	//handle out of bounds x
	if (new_pos.getX() < halfWidth && new_pos.getX() < (int)WM.getBoundary().getHorizontal() / 2) { //character went out of bounds on left side
		WM.moveObject(this, Vector(halfWidth, getPosition().getY()));
		return;
	}
	else if (new_pos.getX() > halfWidth && new_pos.getX() > (int)WM.getBoundary().getHorizontal() - halfWidth) { //character went out of bounds of right side
		WM.moveObject(this, Vector(WM.getBoundary().getHorizontal() - halfWidth, getPosition().getY()));
		return;
	}
	//handle out of bounds y
	else if (new_pos.getY() > 3 && new_pos.getY() < WM.getBoundary().getVertical()){
		WM.moveObject(this, new_pos);
		return;
	}
	
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