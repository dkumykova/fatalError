#include "Object.h"
#include <EventCollision.h>


class CommentWall : public df::Object {
private:
	int wallCountdown;
public:
	CommentWall();
	int eventHandler(const df::Event* p_e);
	void collide(const df::EventCollision* p_e);
	void step();
	void setWallCountdown(int num);
	int getWallCountdown() const;

};

