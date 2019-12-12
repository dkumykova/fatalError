//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "vs-2019/Bullet.h"
#include "vs-2019/Star.h"
#include "vs-2019/GameStart.h"
#include "Pause.h"
#include "WorldManager.h"
#include "DisplayManager.h"


using namespace df;
void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {
	 
  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
	
    GM.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);
 
  
 

  // Show splash screen.
  df::splash();

  //load stuff
  loadResources();
  //populate
  populateWorld();
  
  new df::Pause(df::Keyboard::F10);

  GM.run();

  // Shut everything down.
  GM.shutDown();
}


void loadResources(void) {
	//load saucer sprite
	RM.loadSprite("sprites/bullet-spr.txt", "bullet");
	RM.loadSprite("sprites/gameover-spr.txt", "gameover");
	RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
	RM.loadSprite("sprites/platform2-spr.txt", "platform");
	RM.loadSprite("sprites/title-screen-spr.txt", "title");
	RM.loadSprite("sprites/explosion-spr.txt", "explosion");

	RM.loadSprite("sprites/player1select-spr.txt", "select");
	RM.loadSprite("sprites/menu-reticle1-spr.txt", "menureticle1");
	RM.loadSprite("sprites/menu-reticle2-spr.txt", "menureticle2");
	RM.loadSprite("sprites/one-is-selected-spr.txt", "selected1");
	RM.loadSprite("sprites/two-is-selected-spr.txt", "selected2");
	RM.loadSprite("sprites/two-is-unselected-spr.txt", "unselected2");
	RM.loadSprite("sprites/one-is-unselected-spr.txt", "unselected1");
	RM.loadSprite("sprites/KO-spr.txt", "KO");

	RM.loadSprite("sprites/Character_C-spr.txt", "Character_C");
	RM.loadSprite("sprites/Character_C_flipped-spr.txt", "Character_C_flip");
	RM.loadSprite("sprites/Character_C_error-spr.txt", "Character_C_error");
	RM.loadSprite("sprites/Character_C_pointer-spr.txt", "Character_C_pointer");
	RM.loadSprite("sprites/Character_C_pointer_flipped-spr.txt", "Character_C_pointer_flipped");

	RM.loadSprite("sprites/Character_CPP-spr.txt", "Character_CPP");
	RM.loadSprite("sprites/Character_CPP_flipped-spr.txt", "Character_CPP_flip");
	RM.loadSprite("sprites/Character_CPP_plus-spr.txt", "Character_CPP_Plus");
	RM.loadSprite("sprites/Character_CPP_error-spr.txt", "Character_CPP_error");

	RM.loadSprite("sprites/Character_Python-spr.txt", "Character_Python");
	RM.loadSprite("sprites/Character_Python_flipped-spr.txt", "Character_Python_flip");
	RM.loadSprite("sprites/Character_Python_error-spr.txt", "Character_Python_error");

	RM.loadSprite("sprites/Character_Lisp-spr.txt", "Character_Lisp");
	RM.loadSprite("sprites/Character_Lisp_flipped-spr.txt", "Character_Lisp_flip");
	RM.loadSprite("sprites/Character_Lisp_error-spr.txt", "Character_Lisp_error");
	RM.loadSprite("sprites/Character_Lisp_super-spr.txt", "Character_Lisp_super");

	RM.loadSprite("sprites/Character_Java-spr.txt", "Character_Java");
	RM.loadSprite("sprites/Character_Java_flipped-spr.txt", "Character_Java_flip");
	RM.loadSprite("sprites/Character_Java_error-spr.txt", "Character_Java_error");
	RM.loadSprite("sprites/Character_Java_super-spr.txt", "Character_Java_super");

	RM.loadSprite("sprites/Character_Js-spr.txt", "Character_Js");
	RM.loadSprite("sprites/Character_Js_flipped-spr.txt", "Character_Js_flip");
	RM.loadSprite("sprites/Character_Js_error-spr.txt", "Character_Js_error");
	RM.loadSprite("sprites/Character_Js_super-spr.txt", "Character_Js_super");

	RM.loadSprite("sprites/comment-wall-spr.txt", "commentwall");
	RM.loadSprite("sprites/paren-spr.txt", "paren");

	RM.loadSprite("sprites/Controls-spr.txt", "controls");
	RM.loadSprite("sprites/pressT-spr.txt", "pressT");


	RM.loadSound("sounds/fire.wav", "fire");
	RM.loadSound("sounds/explode.wav", "explode");
	RM.loadSound("sounds/nuke.wav", "nuke");
	RM.loadSound("sounds/game-over.wav", "gameOver");
	RM.loadSound("sounds/health-pickup.wav", "healthpickup");

	RM.loadMusic("sounds/start_music_fight.wav", "startMusic");
	RM.loadMusic("sounds/play_music_fight.wav", "gameMusic");
}


void populateWorld(void) {
	

	for (int j = 0; j < 15; j++) {
		new Star;
	}

	new GameStart();

}

