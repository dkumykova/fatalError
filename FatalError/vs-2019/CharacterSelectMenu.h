#include "Object.h"
#include "Player1Reticle.h"
#include "Player2Reticle.h"
#include <Music.h>


class CharacterSelectMenu : public df::Object {
private:
	Music* game_music;
	Music* start_music;
public:
	CharacterSelectMenu();
	void start();
	bool checkReady();
	//put both reticles in here so you can access if they have selected character or not
	Player1Reticle* player1;
	Player2Reticle* player2;
	int eventHandler(const df::Event* p_e);
	void setStartMusic(Music* m);
	Music* getGameMusic() const;

};

