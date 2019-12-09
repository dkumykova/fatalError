#include "TestCharacter2.h"
#include "WorldManager.h"
#include "GameOver.h"
#include <LogManager.h>

TestCharacter2::TestCharacter2() {
	//link to ship sprite
	setSprite("test character");

	// Set Type
	setType("TestCharacter2");

	// Set Starting Position
	df::Vector position(100, WM.getBoundary().getVertical() / 2);
	setPosition(position);
}

