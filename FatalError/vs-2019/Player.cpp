
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

	registerInterest(df::KEYBOARD_EVENT); // Listen to Keyboard Events
	registerInterest(df::STEP_EVENT); // Listen to Keyboard Events

	facing_right = true;
	setSolidness(df::SPECTRAL);

}

// General Event Handler
int Player::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {

		// If originally at other player's left and now become right
		if (facing_right) {
			if (getLeftBoundary() > getOpponentPlayer()->getRightBoundary() + 10) {
				swapFacing();
				m_p_character->flipSprite(PlayerCharacter::SpriteStatus::Flipped);
			}
		}
		else { // Else if originally at other player's right and now become left
			if (getRightBoundary() < getOpponentPlayer()->getLeftBoundary() - 10 && !facing_right) {
				swapFacing();
				m_p_character->flipSprite(PlayerCharacter::SpriteStatus::Original);
			}
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
	// No implementation because this is player dependent
}

void Player::setOpponentPlayer(Player* new_player){
	m_p_other_player = new_player;
}

Player* Player::getOpponentPlayer() const{
	return m_p_other_player;
}

float Player::getLeftBoundary(){
	return df::getWorldBox(m_p_character).getCorner().getX();
}

float Player::getRightBoundary(){
	return df::getWorldBox(m_p_character).getCorner().getX() + m_p_character->getBox().getHorizontal();
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
