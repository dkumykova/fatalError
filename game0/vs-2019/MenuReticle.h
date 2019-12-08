#ifndef __MENU_RETICLE_H__
#define __MENU_RETICLE_H__

#include "Object.h"
#include "EventKeyboard.h"
#include "PlayerSelected.h"
using namespace df;

class MenuReticle : public df::Object {
private:
	void virtual kbd(const df::EventKeyboard* p_key_event);
	void step();
	int move_slowdown;
	int move_countdown;
	Vector highlightedChar;
	bool characterSet; //true if character has been selected
	


public:
	MenuReticle();
	void move(int dy);
	int eventHandler(const df::Event* p_e);
	~MenuReticle();
	void setHighlightedChar(Vector pos);
	Vector getHighlightedChar() const;
	void setCharacterSet(bool isSet);
	bool getCharacterSet() const;
	PlayerSelected* selectedString;


};
#endif

