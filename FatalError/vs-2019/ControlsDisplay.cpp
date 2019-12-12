#include "ControlsDisplay.h"

ControlsDisplay::ControlsDisplay() {
	setType("controls");
	setSprite("controls");
	setSolidness(df::SPECTRAL);

	
	erase = false;
}

bool ControlsDisplay::getErase() const {
	return erase;
}
void ControlsDisplay::setErase(bool o) {
	erase = o;
}