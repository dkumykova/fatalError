#include "JavaClone.h"
#include "EventHealth.h"
#include <EventOut.h>

JavaClone::JavaClone(df::Vector dir) {
	setType("clone");
	setSprite("Character_Java");
	
	registerInterest(HEALTH_EVENT);
	registerInterest(df::OUT_EVENT);
	df::Vector p(dir.getX() + 3, dir.getY());
	setPosition(p);
}
int JavaClone::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		//out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == HEALTH_EVENT) {

		return 1;
	}


	return 0;
}

void JavaClone::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1() == this) &&
		(p_collision_event->getObject2() == this)) {
	}
	//if bullet hits player 1
	if ((p_collision_event->getObject1()->getType() == "PlayerCharacter") &&
		(p_collision_event->getObject2()->getType() != "PlayerCharacter")) {

		if (p_collision_event->getObject1()->getType() == "PlayerCharacter") {
			//PlayerCharacter* p_c = dynamic_cast <PlayerCharacter*> (p_collision_event->getObject1());
			//Player* p_p = p_c->getPlayer();
			////reduce hero health
			//LM.writeLog("bananan");
			//p_p->handleHealth(p_c->getAttackOneDamage());
			//if (p_p->getHealth() <= 0) {
			//	p_c->getFrozen(5);
			//	WM.markForDelete(p_collision_event->getObject1());
			//	new GameOver();
			//}
			//WM.markForDelete(p_collision_event->getObject2());
		}

		if (p_collision_event->getObject2()->getType() == "PlayerCharacter") {
			//PlayerCharacter* p_c = dynamic_cast <PlayerCharacter*> (p_collision_event->getObject2());
			//Player* p_p = p_c->getPlayer();
			////reduce hero health
			//LM.writeLog("bananan");

			//p_p->handleHealth(p_c->getAttackTwoDamage());
			//if (p_p->getHealth() <= 0) {
			//	p_c->getFrozen(5);
			//	WM.markForDelete(p_collision_event->getObject2());
			//	new GameOver();
			//}
			//WM.markForDelete(p_collision_event->getObject1());
		}
	}
}