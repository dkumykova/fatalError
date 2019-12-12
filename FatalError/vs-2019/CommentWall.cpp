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
	damageSaved = 0;
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
	//change to projectile when merge
	if (p_e->getObject1()->getType() == "Bullet" || p_e->getObject2()->getType() == "Bullet") {
		//block object + destroy
		LM.writeLog("wall collided with projectile!");
		if (p_e->getObject1()->getType() == "Bullet") {
			
			WM.markForDelete(p_e->getObject1());
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

void CommentWall::setDamageSaved(int num) {
	damageSaved = num;
}
int CommentWall::getDamageSaved() const {
	return damageSaved;
}