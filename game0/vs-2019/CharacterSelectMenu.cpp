
#include "CharacterSelectMenu.h"

CharacterSelectMenu::CharacterSelectMenu() {
	//link to sprite
	setSprite("select");
	setSolidness(df::SPECTRAL);
	setType("select");
	df::Vector p(100, 25); 
	setPosition(p);
}
