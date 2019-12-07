#ifndef __MENU_RETICLE_H__
#define __MENU_RETICLE_H__

#include "Object.h"
#include "EventKeyboard.h"

class MenuReticle : public df::Object {
private:
	void virtual kbd(const df::EventKeyboard* p_key_event);
	void step();
	int move_slowdown;
	int move_countdown;


public:
	MenuReticle();
	void move(int dy);
	int eventHandler(const df::Event* p_e);
	~MenuReticle();


};
#endif

