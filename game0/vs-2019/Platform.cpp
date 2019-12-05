#include "Platform.h"


Platform::Platform() {
	//link to sprite
	setSprite("platform");

	setType("Platform");
	df::Vector p(40, 16); //place in bottom third of screen
	setPosition(p);

}

//int Platform::draw() {
//
//}