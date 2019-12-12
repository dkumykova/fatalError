#include "Character_pip.h"
#include "Player.h"
#include <EventStep.h>

Character_Pip::Character_Pip(Character_Python* master){

	p_master = master;
	
	setPosition(master->getPosition());

	if (p_master->getPlayer()->getFacingRight() == 1) {
		setSprite("Character_Pip_flipped");
	}
	else {
		setSprite("Character_Pip");
	}

	setSolidness(df::SPECTRAL);
	setAltitude(4);
}

int Character_Pip::eventHandler(const df::Event* p_e){
	if (p_e->getType() == df::STEP_EVENT) {
		if (p_master->getPlayer()->getFacingRight() == 1) {
			setSprite("Character_Pip_flipped");
		}
		else {
			setSprite("Character_Pip");
		}

		float x = p_master->getPosition().getX() - p_master->getPlayer()->getOpponentPlayer()->getCharacter()->getPosition().getX();
		float y = p_master->getPosition().getY() - p_master->getPlayer()->getOpponentPlayer()->getCharacter()->getPosition().getY();
		df::Vector p(x, y);

		if (p.getMagnitude() < 50) {
			if (p_master->getPlayer()->getFacingRight() == 1) {
				setSprite("Character_Pip_attacking_flipped");
				p_master->attackingbot(5);
			}
			else {
				setSprite("Character_Pip_flipped");
				p_master->attackingbot(5);
			}
		}

		setPosition(df::Vector(getPosition().getX() + p_master->getPlayer()->getFacingRight() * 1, getPosition().getY()));
		return 1;
	}

	return 0;
}
