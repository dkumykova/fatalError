#include "Character_pip.h"
#include "Player.h"
#include <EventStep.h>

Character_Pip::Character_Pip(Character_Python* master){

	p_master = master;
	
	setPosition(df::Vector(master->getPosition().getX(), master->getPosition().getY()-5));

	if (p_master->getPlayer()->getFacingRight() == 1) {
		setSprite("Character_Pip_flipped");
	}
	else {
		setSprite("Character_Pip");
	}

	registerInterest(STEP_EVENT);
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

		float x = getPosition().getX() - p_master->getPlayer()->getOpponentPlayer()->getCharacter()->getPosition().getX();
		float y = getPosition().getY() - p_master->getPlayer()->getOpponentPlayer()->getCharacter()->getPosition().getY();
		df::Vector p(x, y);

		if (p.getMagnitude() < 10) {
			if (p_master->getPlayer()->getFacingRight() == 1) {
				setSprite("Character_Pip_attacking_flipped");
				p_master->attackingbot(1);
			}
			else {
				setSprite("Character_Pip_flipped");
				p_master->attackingbot(1);
			}
		}

		df::Vector m(x, 0);
		m.normalize();
		setPosition(df::Vector(getPosition().getX() + m.getX() * 0.1 * -1, getPosition().getY()));
		return 1;
	}

	return 0;
}
