#include "Object.h"
//#include "PlayerCharacter.h"
#include <EventCollision.h>

#ifndef __COMMENT_WALL_H__
#define __COMMENT_WALL_H__

using namespace df;
class CommentWall : public df::Object {
private:
	int wallCountdown;
	int damageSaved;
	//PlayerCharacter* character;
public:
	CommentWall();
	int eventHandler(const df::Event* p_e);
	void collide(const df::EventCollision* p_e);
	void step();
	void setWallCountdown(int num);
	int getWallCountdown() const;
	void setDamageSaved(int num);
	int getDamageSaved() const;
	/*PlayerCharacter* getPlayer() const;
	void setPlayer(PlayerCharacter *p);*/

};
#endif

