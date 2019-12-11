#include "GameOver.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Sound.h"
#include "GameStart.h"
#include <LogManager.h>
#include "CharacterSelectMenu.h"

GameOver::GameOver() {
	if (setSprite("KO") == 0) {
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	}
	else {
		time_to_live = 0;
	}
	
	registerInterest(df::STEP_EVENT);

	setLocation(df::CENTER_CENTER);

	df::Sound* p_sound = RM.getSound("gameOver");
	//p_sound->play();

}

int GameOver::eventHandler(const df::Event *p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	return 0;
}

void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0) {
		WM.markForDelete(this);
	}
}

GameOver::~GameOver() {
	LM.writeLog("Game over");
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {

		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "select") {
			CharacterSelectMenu* c = dynamic_cast <CharacterSelectMenu*> (p_o);
			c->getGameMusic()->pause();
			
		}
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true);
			continue;
			//pause game music and play menu music again
			LM.writeLog("hit game start in game over");
			dynamic_cast <GameStart*> (p_o)->playMusic(dynamic_cast <GameStart *> (p_o)->start_music); 
		}

		if (p_o->getType() == "Star")
			continue;

		WM.markForDelete(p_o);
		//if (p_o->getType() == "Player" || p_o->getType() == "Platform" || p_o->getType() == "Bullet" 
		//	|| p_o->getType() == "ViewObject" || p_o->getType() == "TestCharacter2") {
		//	WM.markForDelete(p_o);
		//}	
	}
	//GM.setGameOver();
}

int GameOver::draw() {
	return df::Object::draw();
}