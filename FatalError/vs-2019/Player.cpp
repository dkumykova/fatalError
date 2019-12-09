
// Game Include
#include "Player.h"

// Event Include
#include "EventHealth.h"
#include <EventStep.h>

// Engine Include
#include <WorldManager.h>
#include <LogManager.h>

Player::Player() {
	setType("Player");

	setHealth(PLAYER_MAX_HEALTH); // Initialize m_health
	my_clock = new Clock(); // Initialize Clock

	registerInterest(df::KEYBOARD_EVENT); // Listen to Keyboard Events
	registerInterest(df::STEP_EVENT); // Listen to Keyboard Events

	facing_right = true;

}

// General Event Handler
int Player::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {

		LM.writeLog("Player Facing %d", getFacingRight());
		if ((getPosition().getX() > 100 && facing_right) || (getPosition().getX() < 100 && !facing_right)) {
			swapFacing();
		}
		return 1;
	}

	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}

	if (p_e->getType() == HEALTH_EVENT) {
		int damage = 20;
		handleHealth(damage);
		return 1;
	}

	return 0;
}

// Keyboard Listener and Processor
void Player::kbd(const df::EventKeyboard* p_key_event){
	// No implementation because this is player dependent
}

void Player::setHealth(int health){
	m_health = health;
}

int Player::getHealth() const{
	return m_health;
}

void Player::handleHealth(int damage){
	// No implementation because this is player dependent
}

void Player::setCharacter(PlayerCharacter* new_char){
	m_p_character = new_char;
}

int Player::getFacingRight(){
	if (facing_right)
		return 1;
	else
		return -1;
}

void Player::swapFacing(){
	facing_right = !facing_right;
}
