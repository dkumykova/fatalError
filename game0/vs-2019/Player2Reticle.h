#ifndef __PLAYER2_RETICLE_H__
#define __PLAYER2_RETICLE_H__

#include "Object.h"
#include "MenuReticle.h"

class Player2Reticle : public MenuReticle {

public:
	Player2Reticle();
	//int eventHandler(const df::Event* p_e);
	~Player2Reticle();
	void kbd(const df::EventKeyboard* p_key_event);


};
#endif

