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
	setSolidness(df::SPECTRAL);
	swapFacing();
}

void PlayerTwo::kbd(const df::EventKeyboard* p_key_event){
	switch (p_key_event->getKey()) {
	case df::Keyboard::UPARROW:       // Jump
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
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
	case df::Keyboard::LEFTARROW:       // Left
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			m_p_character->moveLeft();
			return;
		}
		break;
	case df::Keyboard::DOWNARROW:       // Defend
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			//
			break;
	case df::Keyboard::RIGHTARROW:       // Right
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
	case df::Keyboard::J: // attack 1
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->attack_1();
		break;
	case df::Keyboard::K: // attack 2
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			m_p_character->attack_2();
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
}
