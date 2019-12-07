#include "TestingCharacter.h"
#include "WorldManager.h"

TestCharacter::TestCharacter(){
	//link to ship sprite
	setSprite("test character");

	// Set Type
	setType("TestCharacter");

	// Set Starting Position
	df::Vector position(20, WM.getBoundary().getVertical() / 2);
	setPosition(position);
}
