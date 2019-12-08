#include "Bullet.h"
#include "WorldManager.h"
#include "Saucer.h"
#include "EventOut.h"
#include "TestingCharacter.h"
#include "TestCharacter2.h"
#include "EventHealth.h"
#include "GameOver.h"
#include <LogManager.h>

Bullet::Bullet(df::Vector hero_position) {
	//link to sprite
	setSprite("bullet");

	setType("Bullet");
	df::Vector p(hero_position.getX() + 3, hero_position.getY());
	setPosition(p);
	//make bullets soft so can pass through Hero
	setSolidness(df::SOFT);
	registerInterest(HEALTH_EVENT);


	//bullets move 1 space each game loop
	//direction set when hero fires
	setSpeed(1);
}

int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision *> (p_e);
		hit(p_collision_event);
		return 1;
	}
	if (p_e->getType() == HEALTH_EVENT) {

		return 1;
	}

	
	return 0;
}

void Bullet::out() {
	WM.markForDelete(this);
}

//if bullet hits saucer, mark both for deletion
void Bullet::hit(const df::EventCollision *p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Saucer") ||
		(p_collision_event->getObject2()->getType() == "Saucer")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}

	//if bullet hits player 1
	if ((p_collision_event->getObject1()->getType() == "TestCharacter") ||
		(p_collision_event->getObject2()->getType() == "TestCharacter")) {

		LM.writeLog("Hitting player1");
		if (p_collision_event->getObject1()->getType() == "TestCharacter") {
			TestCharacter* hero = dynamic_cast <TestCharacter*> (p_collision_event->getObject1());
			//reduce hero health
			hero->handleHealth();
			if (hero->getHealth() <= 0) {
				WM.markForDelete(p_collision_event->getObject1());
				new GameOver();
			}
			WM.markForDelete(p_collision_event->getObject2());
		}

		if (p_collision_event->getObject2()->getType() == "TestCharacter") {
			TestCharacter* hero = dynamic_cast <TestCharacter*> (p_collision_event->getObject2());
			//reduce hero health
			hero->handleHealth();
			if (hero->getHealth() <= 0) {
				WM.markForDelete(p_collision_event->getObject2());
				new GameOver();
			}
			WM.markForDelete(p_collision_event->getObject1());
		}
	}

	//if bullet hits player 2
	if ((p_collision_event->getObject1()->getType() == "TestCharacter2") ||
		(p_collision_event->getObject2()->getType() == "TestCharacter2")) {
		LM.writeLog("Hitting player2");

		if (p_collision_event->getObject1()->getType() == "TestCharacter2") {
			TestCharacter2* hero = dynamic_cast <TestCharacter2*> (p_collision_event->getObject1());
			//reduce hero health
			hero->handleHealth();
			if (hero->getHealth() <= 0) {
				WM.markForDelete(p_collision_event->getObject1());
				new GameOver();
			}
			WM.markForDelete(p_collision_event->getObject2());
			
		}

		if (p_collision_event->getObject2()->getType() == "TestCharacter2") {
			TestCharacter2* hero = dynamic_cast <TestCharacter2*> (p_collision_event->getObject2());
			//reduce hero health
			hero->handleHealth();
			if (hero->getHealth() <= 0) {
				WM.markForDelete(p_collision_event->getObject2());
				new GameOver();
			}
			WM.markForDelete(p_collision_event->getObject1());
		}
	}
}