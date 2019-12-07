
#include "CharacterSelectMenu.h"
#include "Platform.h"
#include "TestingCharacter.h"
#include <EventStep.h>
#include <LogManager.h>

CharacterSelectMenu::CharacterSelectMenu() {
	//link to sprite
	setSprite("select");
	setSolidness(df::SPECTRAL);
	setType("select");
	df::Vector p(100, 25); 
	setPosition(p);

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);

	player1 = new Player1Reticle();
	player2 = new Player2Reticle();
}

void CharacterSelectMenu::start() {
	//transition to actual game screen with correct characters selected
	if (player1->getCharacterSet() && player2->getCharacterSet()) {
		//both players have selected their character and game is ready to go
		LM.writeLog("Both characters have been set!");
		
		new Platform();

		//this should be replaced with 2 chosen characters based on getHighlightedChar function for each reticle + switch statement
		new TestCharacter();
		setActive(false);
		player1->setActive(false);
		player2->setActive(false);


	}
	else {
		LM.writeLog("Characters have not been set!");
	}

}

int CharacterSelectMenu::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_key_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);

		switch (p_key_event->getKey()) {
		case df::Keyboard::SPACE:

			if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
				start();
				return 1;
			}
			break;

		default:
			break;
		}
		return 1;
		
	}
	if (p_e->getType() == df::STEP_EVENT) {
		//step();
		return 1;
	}
	return 0;
}
