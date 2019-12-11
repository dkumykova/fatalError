#include "LispSuper.h"
#include <EventStep.h>
#include <LogManager.h>
#include <WorldManager.h>
#include "PlayerCharacter.h"
#include "Player.h"
#include "GameOver.h"


LispSuper::LispSuper() {
	setSprite("Character_Lisp_super");
	setType("super");
	countdown = 100;
	setAltitude(1);
	setSolidness(SOFT);

	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);
}
int LispSuper::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		collide(p_collision_event);
		return 0;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 0;
	}
	return 1;
}
void LispSuper::collide(const df::EventCollision* p_e) {
	//change to projectile when merge
	if (p_e->getObject1()->getType() == "Bullet" || p_e->getObject2()->getType() == "Bullet") {
		//block object + destroy
		LM.writeLog("wall collided with projectile!");
		if (p_e->getObject1()->getType() == "PlayerCharacter" || p_e->getObject2()->getType() == "PlayerCharacter") {
			if (p_e->getObject1()->getType() == "PlayerCharacter") {
				
				PlayerCharacter* p = dynamic_cast <PlayerCharacter*> (p_e->getObject1());
				LM.writeLog("super hit a player!");
				//PlayerCharacter* p_c = dynamic_cast <PlayerCharacter*> (p_collision_event->getObject1());
				//Player* p_p = p_c->getPlayer();
				//reduce hero health
				Player* p_p = p->getPlayer();
				
				p_p->handleHealth(p->getSuperDamage());

				if (p_p->getHealth() <= 0) {
					p->getFrozen(5);
					WM.markForDelete(p);
					new GameOver();
				}
				/*WM.markForDelete(p_collision_event->getObject2());*/
			}

			if (p_e->getObject2()->getType() == "PlayerCharacter") {

				PlayerCharacter* p = dynamic_cast <PlayerCharacter*> (p_e->getObject2());
				LM.writeLog("super hit a player!");
				//PlayerCharacter* p_c = dynamic_cast <PlayerCharacter*> (p_collision_event->getObject1());
				//Player* p_p = p_c->getPlayer();
				//reduce hero health
				Player* p_p = p->getPlayer();

				p_p->handleHealth(p->getSuperDamage());

				if (p_p->getHealth() <= 0) {
					p->getFrozen(5);
					WM.markForDelete(p);
					new GameOver();
				}
				/*WM.markForDelete(p_collision_event->getObject2());*/
			}
			//WM.markForDelete(p_e->getObject1());
			//might be able to get away with just adding to health
			//player->handleHealth(-20); //reduce damage by 20
			//handle health by reducing health by projectile damage amount + wall padding
		}
		else if (p_e->getObject2()->getType() == "Bullet") {
			WM.markForDelete(p_e->getObject2());
			//handle health by reducing health by projectile damage amount + wall padding
		}

	}
}
void LispSuper::step() {
	LM.writeLog("wall step called");
	LM.writeLog("wall countdown value: " + countdown);
	if (countdown == 0) {
		setActive(false); //remove wall
		countdown = 100; //reset
		return;
	}
	else {
		//WM.moveObject();
		countdown--; //countdown

	}
}
void LispSuper::setCountdown(int num) {
	countdown = num;
}
int LispSuper::getCountdown() const {
	return countdown;
}