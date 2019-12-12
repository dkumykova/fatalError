#include "Character_CPP_plus.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "PlayerCharacter.h"
#include "Player.h"
#include <EventStep.h>
#include "GameOver.h"
#include <LogManager.h>
#include "Character_C.h"

Character_CPP_Plus::Character_CPP_Plus(df::Vector position, int speed, int time) {
	//link to sprite
	setSprite("Character_CPP_Plus");

	setType("melee sword");
	setPosition(position);

	//make Character_CPP_Pluss soft so can pass through Hero
	setSolidness(df::SOFT);

	//Character_CPP_Pluss move 1 space each game loop
	//direction set when hero fires
	m_speed = speed;
	setVelocity(df::Vector(0, 0.15 * speed));
	time_to_live = time;

	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);
}

int Character_CPP_Plus::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

void Character_CPP_Plus::out() {
	WM.markForDelete(this);
}

//if Character_CPP_Plus hits saucer, mark both for deletion
void Character_CPP_Plus::hit(const df::EventCollision* p_collision_event) {

	//if Character_CPP_Plus hits player 1
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

//Count till end
void Character_CPP_Plus::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);

	if (getVelocity().getY() > 3 + m_speed * 0.1)
		setVelocity(df::Vector(0, 3 + m_speed * 0.1));
}