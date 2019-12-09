
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
	setSolidness(df::SPECTRAL);
}

void PlayerOne::kbd(const df::EventKeyboard* p_key_event){
	switch (p_key_event->getKey()) {
	case df::Keyboard::W:       // Jump
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			//LM.writeLog("Player One Key down W*");
			long int jump_time = my_clock->split() / 1000;

			if (jump_time < 1000) {
				//LM.writeLog("Too quick to jump!");
				//LM.writeLog("%ld", jump_time);
				return;
			}

			my_clock->delta(); // Reset Clock
			m_p_character->jump(); // Jump
		}
		break;
	case df::Keyboard::A:       // Left
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			m_p_character->moveLeft();
			return;
		}
		break;
	case df::Keyboard::S:       // Defend
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			//
			break;
	case df::Keyboard::D:       // Right
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			m_p_character->moveRight();
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
}
