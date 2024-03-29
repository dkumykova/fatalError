
// Game Include
#include "CharacterSelectMenu.h"
#include "Platform.h"
#include "PlayerOne.h"
#include "PlayerTwo.h"
#include "PlayerCharacter.h"
#include <ViewObject.h>
#include "TestCharacter2.h"
#include "Explosion.h"

// Character Includes
#include "Character_C.h"
#include "Character_CPP.h"
#include "Character_Python.h"

// Event Include
#include <EventStep.h>

// Engine Include
#include <LogManager.h>
#include "Character_Lisp.h"
#include <ResourceManager.h>


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


		PlayerOne* p1 = new PlayerOne;
		PlayerTwo* p2 = new PlayerTwo;

		PlayerCharacter* c1 = player1->getHighlightedChar();
		PlayerCharacter* c2 = player2->getHighlightedChar();

		p1->setCharacter(c1);
		c1->setPlayer(p1);
		p1->setOpponentPlayer(p2);
		p2->setCharacter(c2);
		c2->setPlayer(p2);
		p2->setOpponentPlayer(p1);

		setActive(false);
		player1->setActive(false);
		player2->setActive(false);
		player1->selectedString->setActive(false);
		player2->selectedString->setActive(false);
		c1->setActive(true);
		c2->setActive(true);

		df::ViewObject* p_health = new df::ViewObject; //keep track of health
		p_health->setLocation(df::TOP_LEFT);
		p_health->setViewString("Player 1 Health:");
		p_health->setValue(100);
		p_health->setColor(df::GREEN);

		df::ViewObject* p_health2 = new df::ViewObject; //keep track of health
		p_health2->setLocation(df::TOP_RIGHT);
		p_health2->setViewString("Player 2 Health:");
		p_health2->setValue(100);
		p_health2->setColor(df::GREEN);

		game_music = RM.getMusic("gameMusic");
		start_music->pause();

		game_music->play();

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

void CharacterSelectMenu::setStartMusic(Music* m) {
	start_music = m;
}

Music* CharacterSelectMenu::getGameMusic() const{
	return game_music;
}