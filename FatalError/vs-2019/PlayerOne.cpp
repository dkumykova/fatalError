
// Game Include
#include "PlayerOne.h"
#include "GameOver.h"

// Event Include
#include <EventView.h>

// Engine Indlude
#include <WorldManager.h>
#include <LogManager.h>

// Keyboard Listen Implementation of Player One

PlayerOne::PlayerOne() {
	setPosition(df::Vector(20, WM.getBoundary().getVertical() / 2));
}

void PlayerOne::kbd(const df::EventKeyboard* p_key_event){
	switch (p_key_event->getKey()) {
	case df::Keyboard::W:       // Process Up
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			m_p_character->processUpArrow();
		}
		break;
	case df::Keyboard::A:       // Process Left
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			m_p_character->processLeftArrow();
		}
		break;
	case df::Keyboard::S:       // Process Down
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			m_p_character->processDownArrow();
		break;
	case df::Keyboard::D:       // Process Right
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
	case df::Keyboard::C: // attack 1
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->attack_1();
		break;
	case df::Keyboard::V: // attack 2
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->attack_2();
		break;
	case df::Keyboard::F: // defend //******NOTE HERE WE HAVE 2 SPECIALS
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->do_action_defense(m_p_character->getIsHigherLevel());
		break;
	//case df::Keyboard::T: // controls
	//	if (p_key_event->getKeyboardAction() == df::KEY_PRESSED) {
	//		if (getControls()->isActive()) {
	//			setActive(false);
	//		}
	//		else {
	//			getControls()->setPosition(Vector(50, 10));
	//			getControls()->setActive(true);
	//		}

	//	}
	//	break;
	//case df::Keyboard::G: // super
	//	if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
	//		m_p_character->do_action_super_attack();
	//	break;

	case df::Keyboard::G: // Super Attack
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->specialAttack();
		break;
	default: // Key not handled.
		return;
	};
	return;
}

// Health Event Handler
void PlayerOne::handleHealth(int damage){
	if (!getHealth()) {
		return;
	}

	// Update Health
	setHealth(getHealth() - damage);

	// Update Health Bar
	df::EventView ev("Player 1 Health:", -damage, true);
	WM.onEvent(&ev);
	if (getHealth() <= 0) {
		m_p_character->getFrozen(10);
		WM.markForDelete(m_p_character);
		new GameOver;
	}
}

void PlayerOne::setCharacter(PlayerCharacter* new_char) {
	m_p_character = new_char;
}
