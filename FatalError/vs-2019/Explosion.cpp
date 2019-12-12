// Explosion.cp

#include "Explosion.h"
#include "EventStep.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"


Explosion::Explosion() {
	// Register Interest
	registerInterest(df::STEP_EVENT);

	// Set Sprite with Check
	if (setSprite("explosion") == 0)
		// Get time to live from sprite
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();

	else
		time_to_live = 0;

	setType("Explosion");

	setSolidness(df::SPECTRAL);
}

int Explosion::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

//Count till end
void Explosion::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}
