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

	// Counter Attributes (All with basic initialization values)
	horizontal_move_slowdown = 2;
	horizontal_move_countdown = horizontal_move_slowdown;
	jump_slowdown = 30;
	jump_countdown = jump_slowdown;
	attack_1_slowdown = 15;
	attack_1_countdown = attack_1_slowdown;
	attack_2_slowdown = 300;
	attack_2_countdown = 0;
	super_attack_slowdown = 600;
	super_attack_countdown = super_attack_slowdown;
	super_channeling_slowdown = 60;
	super_channeling_countdown = super_channeling_slowdown;
	defense_slowdown = 30;
	defense_countdown = defense_slowdown;

	// Move Related
	jump_speed = INITIAL_JUMP_SPEED;
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

	// Attack Related
	m_super_cast_time = 4;
	m_super_channeling = false;
	m_super_attacking = false;
	setErrorAttacking(false); // Initiate Error Attacking to false
	setAttackOneDamage(10); // If not specifically defined, then it's 10
	setAttackTwoDamage(20); // If not specifically defined, then it's 20

	// Set Solidness
	setSolidness(df::SOFT);
}

PlayerCharacter::~PlayerCharacter() {
	// Mark Reticle for deletion.
	//WM.markForDelete(p_reticle);
	

}

void PlayerCharacter::processRightArrow(){
	// See if time to move.
	if (isTimeToHorizontalMove()) {
		do_action_move_right();
		return;
	}
}

void PlayerCharacter::processLeftArrow(){
	// See if time to move.
	if (isTimeToHorizontalMove()) {
		do_action_move_left();
		return;
	}
}

void PlayerCharacter::processUpArrow(){
	// If during error attacking
	if (getErrorAttacking()) {
		move(0, -0.25);
		return;
	}

	// If not all above, then it's time to jump
	if (isTimeToJump()) {
		do_action_jump();
		setOnGroundStatus(false);
	}
}

void PlayerCharacter::processDownArrow(){
	// If during error attacking
	if (getErrorAttacking()) {
		move(0, 0.25); // Generalized Error Attacking Function
		return;
	}

	// If not all above, then it's time to defense
	do_action_defense();
}

void PlayerCharacter::attack_1() {
	if (isTimeToAttackOne()) {
		do_action_attack_1();
		return;
	}
}

void PlayerCharacter::attack_2() {
	// If Not in Error Attacking Status
	if (isTimeToAttackTwo()){
		on_ground = false;
		flipSprite(SpriteStatus::Error_Attacking); // Flip To Error Attacking Sprite
		setVelocity(df::Vector(1 * getPlayer()->getFacingRight(), -0.4));
		setCharacterAcceleration(df::Vector(0, 0));
		setErrorAttacking(true);
		
	}
}

void PlayerCharacter::specialAttack() {
	if (isTimeToSuperAttack())
		startSuperChanneling();
}

void PlayerCharacter::setAttackOneDamage(int damage) {
	m_attack_1_damage = damage;
}

int PlayerCharacter::getAttackOneDamage() const {
	return m_attack_1_damage;
}

void PlayerCharacter::setAttackTwoDamage(int damage) {
	m_attack_2_damage = damage;
}

int PlayerCharacter::getAttackTwoDamage() const {
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

	// if get super attack end event, then check for caster. If caster is this character, reset counter to slowdown
	// Also remember to turn super_attacking back to false
	// To do

	// If get here, have ignored this event.
	return 0;
}

void PlayerCharacter::step() {
	// Move countdown.
	horizontal_move_countdown--;
	if (horizontal_move_countdown < 0)
		horizontal_move_countdown = 0;

	// Jump countdown.
	jump_countdown--;
	if (jump_countdown < 0)
		jump_countdown = 0;

	// Attack 1 countdown
	attack_1_countdown--;
	if (attack_1_countdown < 0)
		attack_1_countdown = 0;

	// Attack 2 countdown
	attack_2_countdown--;
	if (attack_2_countdown < 0)
		attack_2_countdown = 0;

	// Super Attack countdown
	super_attack_countdown--;
	if (super_attack_countdown < 0)
		super_attack_countdown = 0;
	
	// Super Chaneling countdown
	if (m_super_channeling) { // If started super channeling
		super_channeling_countdown--;
	}

	// Defense countdown
	defense_countdown--;
	if (defense_countdown < 0)
		defense_countdown = 0;
	
	// Super Chanelling Related
	if (super_channeling_countdown <= 0) {
		super_channeling_countdown = super_channeling_slowdown;
		m_super_channeling = false;
		m_super_attacking = true;
		do_action_super_attack();
	}


	if (getErrorAttacking()) {
		acceleration = df::Vector(acceleration.getX() + 0.033, acceleration.getY() + 0.013);
	}
	Vector new_velocity = Vector((getVelocity().getX() + acceleration.getX()),
		(getVelocity().getY() + acceleration.getY()));;
	
	
	// Check for Velocity, Cap it
	if (new_velocity.getX() > TERMINAL_VELOCITY_X&& new_velocity.getY() > TERMINAL_VELOCITY_Y) {
		setVelocity(Vector(TERMINAL_VELOCITY_X, TERMINAL_VELOCITY_Y));
	}
	else if (new_velocity.getX() > TERMINAL_VELOCITY_X) {
		setVelocity(Vector(TERMINAL_VELOCITY_X, getVelocity().getY() + acceleration.getY()));
	}
	else if (new_velocity.getY() > TERMINAL_VELOCITY_Y) {
		setVelocity(Vector(getVelocity().getX() + acceleration.getX(), TERMINAL_VELOCITY_Y));
	}
	else {
		setVelocity(Vector(getVelocity().getX() + acceleration.getX(), getVelocity().getY() + acceleration.getY()));
	}


	
	

	// Error Check for Height
	if (this->getPosition().getY() > 40) {
		this->setPosition(df::Vector(getPosition().getX(), 40));
	}

	if (this->getPosition().getY() < 3) {
		this->setPosition(df::Vector(getPosition().getX(), 3));
	}

	if (this->getPosition().getX() < 0) {
		this->setPosition(df::Vector(getPosition().getX(), 0));
	}

	if (this->getPosition().getY() > 194) {
		this->setPosition(df::Vector(getPosition().getX(), 194));
	}

	stepProcessor();
}

void PlayerCharacter::move(float dx, float dy) {
	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical()))
		WM.moveObject(this, new_pos);
}

// Process General Collisions
void PlayerCharacter::collide(const df::EventCollision* p_c_event) {

	// Helps Only Process when Player Is Not On Ground
	if (!on_ground) {
		if ((p_c_event->getObject1()->getType() == "Platform") ||
			(p_c_event->getObject2()->getType() == "Platform")) {
			LM.writeLog("Collide!!!");
			if (getErrorAttacking()) {
				setErrorAttacking(false);
				attack_2_countdown = attack_2_slowdown;
				if (getPlayer()->getFacingRight() == 1) {
					flipSprite(Original);
				}
				else {
					flipSprite(Flipped);
				}
				setCharacterAcceleration(df::Vector(0, 0.5));
			}

			setOnGroundStatus(true);
			setVelocity(df::Vector(0,0)); //reset velocity to 0
		}
	}

	// Call Character Specific Collision Processor
	processCollision();
}

void PlayerCharacter::flipSprite(SpriteStatus sprite_status){
	// No implementation because this is player dependent
}

void PlayerCharacter::processCollision(){
	// No implementation because this is player dependent
}

void PlayerCharacter::setHorizontalSlowdown(int slowdown, bool counterAlso){
	horizontal_move_slowdown = slowdown;

	if (counterAlso)
		horizontal_move_countdown = horizontal_move_slowdown;
}

void PlayerCharacter::setJumpSlowdown(int slowdown, bool counterAlso){
	jump_slowdown = slowdown;

	if (counterAlso)
		jump_countdown = jump_slowdown;
}

void PlayerCharacter::setDefenseSlowdown(int slowdown, bool counterAlso){
	defense_slowdown = slowdown;

	if (counterAlso)
		defense_countdown = defense_slowdown;
}

void PlayerCharacter::setAttackOneSlowdown(int slowdown, bool counterAlso){
	attack_1_slowdown = slowdown;

	if (counterAlso)
		attack_1_countdown = attack_1_slowdown;
}

void PlayerCharacter::setAttackTwoSlowdown(int slowdown, bool counterAlso){
	attack_2_slowdown = slowdown;

	if (counterAlso)
		attack_2_countdown = attack_2_slowdown;
}

void PlayerCharacter::setSuperAttackSlowdown(int slowdown, bool counterAlso){
	super_attack_slowdown = slowdown;
	
	if (counterAlso)
		super_attack_countdown = super_attack_slowdown;
}

void PlayerCharacter::setSuperChanelingSlowdown(int slowdown, bool counterAlso){
	super_channeling_slowdown = slowdown;

	if (counterAlso)
		super_channeling_countdown = super_channeling_slowdown;
}

void PlayerCharacter::setSuperCastTime(int time){
	m_super_cast_time = time;
}

void PlayerCharacter::do_action_jump(){
	// No implementation because this is player dependent
}

void PlayerCharacter::do_action_defense(){
	// No implementation because this is player dependent
}

void PlayerCharacter::do_action_move_right(){
	// No implementation because this is player dependent
}

void PlayerCharacter::do_action_move_left(){
	// No implementation because this is player dependent
}

void PlayerCharacter::do_action_attack_1(){
	// No implementation because this is player dependent
}

void PlayerCharacter::do_action_attack_2()
{
}

void PlayerCharacter::do_action_super_attack(){
	// No implementation because this is player dependent
}

void PlayerCharacter::stepProcessor(){
	// No implementation because this is player dependent
}

void PlayerCharacter::setCharacterAcceleration(Vector new_a) {
	acceleration = new_a;
}

void PlayerCharacter::setOnGroundStatus(bool status){
	on_ground = status;
}

void PlayerCharacter::setJumpSpeed(float speed){
	jump_speed = speed;
}

float PlayerCharacter::getJumpSpeed() const{
	return jump_speed;
}

void PlayerCharacter::setPlayer(Player* n_player){
	m_p_player = n_player;
	this->setPosition(n_player->getPosition());
}

Player* PlayerCharacter::getPlayer() const {
	return m_p_player;
}