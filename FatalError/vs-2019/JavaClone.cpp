#include "JavaClone.h"
#include "EventHealth.h"
#include <EventOut.h>
#include <EventStep.h>
#include <WorldManager.h>
#include <LogManager.h>
#include "PlayerCharacter.h"
#include "Player.h"
#include "GameOver.h"

JavaClone::JavaClone(df::Vector dir) {
	setType("clone");
	setSprite("Character_Java");
	
	registerInterest(HEALTH_EVENT);
	registerInterest(df::OUT_EVENT);
	registerInterest(df::STEP_EVENT);
	df::Vector p(dir.getX() + 3, dir.getY());
	setPosition(p);
	setSolidness(df::SOFT);
	affect = false;
	countdown = 60;
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
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}


	return 0;
}

void JavaClone::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1() == this) &&
		(p_collision_event->getObject2() == this)) {
		return;
	}
	//if bullet hits player 1
	if ((p_collision_event->getObject1()->getType() == "PlayerCharacter") ||
		(p_collision_event->getObject2()->getType() == "PlayerCharacter")) {
		LM.writeLog("Clone hit target");
		if (p_collision_event->getObject1()->getType() == "PlayerCharacter") {
			PlayerCharacter* p_c = dynamic_cast <PlayerCharacter*> (p_collision_event->getObject1());
			Player* p_p = p_c->getPlayer();
			//reduce hero health
			LM.writeLog("bananan");
			if (getAffect()) {
				p_p->handleHealth(p_c->getAttackOneDamage());
				WM.markForDelete(p_collision_event->getObject2());
			}
			return;
		}

		if (p_collision_event->getObject2()->getType() == "PlayerCharacter") {
			PlayerCharacter* p_c = dynamic_cast <PlayerCharacter*> (p_collision_event->getObject2());
			Player* p_p = p_c->getPlayer();
			//reduce hero health
			LM.writeLog("bananan");
			if (getAffect()) {
				p_p->handleHealth(p_c->getAttackOneDamage());
				WM.markForDelete(p_collision_event->getObject1());
			}
			return;
		}
	}

	if ((p_collision_event->getObject1()->getType() == "Platform") ||
		(p_collision_event->getObject2()->getType() == "Platform")) {
		
		setVelocity(df::Vector(0, 0)); //reset velocity to 0
		setAcceleration(df::Vector(0, 0));

	}
}

void JavaClone::step() {
	
	if (countdown == 0) {
		setActive(false); //remove wall
		WM.markForDelete(this);
		//countdown = 40; //reset
		return;
	}
	else {
		countdown--; //countdown

	}
}

void JavaClone::setAffect(bool t) {
	affect = t;
}

bool JavaClone::getAffect() const{
	return affect;
}