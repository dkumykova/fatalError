#include "Character_C_Pointer.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "PlayerCharacter.h"
#include "Player.h"
#include "EventHealth.h"
#include "GameOver.h"
#include <LogManager.h>
#include "Character_C.h"

Character_C_Pointer::Character_C_Pointer(df::Vector hero_position) {
	//link to sprite
	setSprite("Character_C_pointer");

	setType("projectile");
	df::Vector p(hero_position.getX(), hero_position.getY());
	setPosition(p);

	//make Character_C_Pointers soft so can pass through Hero
	setSolidness(df::SOFT);
	registerInterest(HEALTH_EVENT);


	//Character_C_Pointers move 1 space each game loop
	//direction set when hero fires
	setSpeed(1);
}

int Character_C_Pointer::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

void Character_C_Pointer::out() {
	WM.markForDelete(this);
}

//if Character_C_Pointer hits saucer, mark both for deletion
void Character_C_Pointer::hit(const df::EventCollision* p_collision_event) {

	//if Character_C_Pointer hits player 1
	if ((p_collision_event->getObject1()->getType() == "PlayerCharacter") ||
		(p_collision_event->getObject2()->getType() == "PlayerCharacter")) {

		if (p_collision_event->getObject1()->getType() == "PlayerCharacter") {
			PlayerCharacter* p_c = dynamic_cast <PlayerCharacter*> (p_collision_event->getObject1());
			Player* p_p = p_c->getPlayer();
			//reduce hero health
			p_p->handleHealth(10);
			WM.markForDelete(p_collision_event->getObject2());
		}

		if (p_collision_event->getObject2()->getType() == "PlayerCharacter") {
			PlayerCharacter* p_c = dynamic_cast <PlayerCharacter*> (p_collision_event->getObject2());
			Player* p_p = p_c->getPlayer();
			//reduce hero health
			p_p->handleHealth(10);
			WM.markForDelete(p_collision_event->getObject1());
		}
	}
}