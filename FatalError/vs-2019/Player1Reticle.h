#ifndef __PLAYER1_RETICLE_H__
#define __PLAYER1_RETICLE_H__

#include "Object.h"
#include "MenuReticle.h"

class Player1Reticle: public MenuReticle{

public:
	Player1Reticle();
	//int eventHandler(const df::Event* p_e);
	//~Player1Reticle();
	void kbd(const df::EventKeyboard* p_key_event);


};

#endif
