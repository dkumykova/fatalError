#include "Platform.h"


Platform::Platform() {
	//link to sprite
	setSprite("platform");

	setType("Platform");
	df::Vector p(100, 47); //place in bottom third of screen
	setPosition(p);
	setSolidness(df::HARD);
}

//int Platform::draw() {
//
//}