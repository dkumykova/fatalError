#include "Object.h"
#include "Player1Reticle.h"
#include "Player2Reticle.h"


class CharacterSelectMenu : public df::Object {

public:
	CharacterSelectMenu();
	void start();
	bool checkReady();
	//put both reticles in here so you can access if they have selected character or not
	Player1Reticle* player1;
	Player2Reticle* player2;
	int eventHandler(const df::Event* p_e);

};

