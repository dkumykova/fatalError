#include "CommentWall.h"
#include <EventStep.h>
#include <WorldManager.h>
#include <LogManager.h>



CommentWall::CommentWall() {
	setSprite("commentwall");
	setType("wall");
	setSolidness(df::HARD);

	registerInterest(df::STEP_EVENT);
	registerInterest(df::COLLISION_EVENT);

	wallCountdown = 40; //wall stays up for 10 steps then disappears
}

int CommentWall::eventHandler(const df::Event* p_e) {
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

void CommentWall::collide(const df::EventCollision* p_e) {
	if (p_e->getObject1()->getType() == "projectile" || p_e->getObject2()->getType() == "projectile") {
		//block object + destroy
		LM.writeLog("wall collided with projectile!");

	}
}

void CommentWall::step() {
	LM.writeLog("wall step called");
	LM.writeLog("wall countdown value: " + wallCountdown);
	if (wallCountdown == 0) {
		setActive(false); //remove wall
		wallCountdown = 40; //reset
		return;
	}
	else {
		wallCountdown--; //countdown

	}

}

void CommentWall::setWallCountdown(int num) {
	wallCountdown = num;
}
int CommentWall::getWallCountdown() const {
	return wallCountdown;
}