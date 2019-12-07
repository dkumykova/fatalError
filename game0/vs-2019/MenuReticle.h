#include "Object.h"
#include "EventKeyboard.h"

class MenuReticle : public df::Object {
private:
	void kbd(const df::EventKeyboard* p_key_event);
	void move(int dy);
	void step();
	int move_slowdown;
	int move_countdown;


public:
	MenuReticle();
	int eventHandler(const df::Event* p_e);
	~MenuReticle();


};

