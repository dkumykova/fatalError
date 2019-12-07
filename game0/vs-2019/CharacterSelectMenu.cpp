
#include "CharacterSelectMenu.h"

CharacterSelectMenu::CharacterSelectMenu() {
	//link to sprite
	setSprite("select");
	setSolidness(df::SPECTRAL);
	setType("select");
	df::Vector p(40, 10); //place in bottom third of screen
	setPosition(p);
}
