#pragma once
#include "Object.h"


class ControlsDisplay : public df::Object {
private:
	bool erase;
public:
	ControlsDisplay();
	bool getErase() const;
	void setErase(bool o);
	
};
