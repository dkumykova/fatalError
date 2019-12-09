#include "Platform.h"


Platform::Platform() {
	//link to sprite
	setSprite("platform");

	// Set Basic Attributes
	setType("Platform");
	df::Vector p(100, 47); //place in bottom third of screen
	setPosition(p);
	setAltitude(4);

}

//int Platform::draw() {
//
//}