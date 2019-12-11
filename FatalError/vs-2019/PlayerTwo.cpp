// Player 2

// Game Include 
#include "PlayerTwo.h"
#include "GameOver.h"

// Event Include
#include <EventView.h>

// Engine Include
#include <WorldManager.h>

PlayerTwo::PlayerTwo() {
	setPosition(df::Vector(180, WM.getBoundary().getVertical() / 2));
	swapFacing();
}

void PlayerTwo::kbd(const df::EventKeyboard* p_key_event){
	switch (p_key_event->getKey()) {
	case df::Keyboard::UPARROW:       // Jump
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			m_p_character->processUpArrow(); // Jump
		}
		break;
	case df::Keyboard::LEFTARROW:       // Left
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			m_p_character->processLeftArrow();
		}
		break;
	case df::Keyboard::DOWNARROW:       // Defend
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			m_p_character->processDownArrow();
		break;
	case df::Keyboard::RIGHTARROW:       // Right
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			m_p_character->processRightArrow();
		break;
	case df::Keyboard::ESCAPE:  // quit
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			//new GameOver;
		break;
	case df::Keyboard::R:  // quit
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			new GameOver;
		break;
	case df::Keyboard::J: // attack 1
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->attack_1();
		break;
	case df::Keyboard::K: // attack 2
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->attack_2();
		break;
	case df::Keyboard::L: // Super attack
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->specialAttack();
		break;
	default: // Key not handled.
		return;
	};

	return;
}

void PlayerTwo::handleHealth(int damage){
	if (!getHealth()) {
		return;
	}

	// Update Health
	setHealth(getHealth() - damage);

	// Update Health Bar
	df::EventView ev("Player 2 Health:", -damage, true);
	WM.onEvent(&ev);

	if (getHealth() <= 0) {
		m_p_character->getFrozen(10);
		WM.markForDelete(m_p_character);
		new GameOver;
	}
}

void PlayerTwo::setCharacter(PlayerCharacter* new_char) {
	m_p_character = new_char;
	m_p_character->flipSprite(PlayerCharacter::SpriteStatus::Flipped);
}