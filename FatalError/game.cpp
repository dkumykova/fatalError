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
	RM.loadSprite("sprites/saucer-spr.txt", "saucer");
	RM.loadSprite("sprites/ship-spr.txt", "ship");
	RM.loadSprite("sprites/bullet-spr.txt", "bullet");
	RM.loadSprite("sprites/explosion-spr.txt", "explosion");
	RM.loadSprite("sprites/gameover-spr.txt", "gameover");
	RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
	RM.loadSprite("sprites/healthpack-spr.txt", "healthpack");
	RM.loadSprite("sprites/platform2-spr.txt", "platform");
	RM.loadSprite("sprites/title-screen-spr.txt", "title");
	RM.loadSprite("sprites/testchar-spr.txt", "test character");
	RM.loadSprite("sprites/player1select-spr.txt", "select");
	RM.loadSprite("sprites/menu-reticle1-spr.txt", "menureticle1");
	RM.loadSprite("sprites/menu-reticle2-spr.txt", "menureticle2");
	RM.loadSprite("sprites/one-is-selected-spr.txt", "selected1");
	RM.loadSprite("sprites/two-is-selected-spr.txt", "selected2");
	RM.loadSprite("sprites/two-is-unselected-spr.txt", "unselected2");
	RM.loadSprite("sprites/one-is-unselected-spr.txt", "unselected1");
	RM.loadSprite("sprites/KO-spr.txt", "KO");

	RM.loadSound("sounds/fire.wav", "fire");
	RM.loadSound("sounds/explode.wav", "explode");
	RM.loadSound("sounds/nuke.wav", "nuke");
	RM.loadSound("sounds/game-over.wav", "gameOver");
	RM.loadSound("sounds/health-pickup.wav", "healthpickup");

	RM.loadMusic("sounds/start-music.wav", "startMusic");
	RM.loadMusic("sounds/game-music.wav", "gameMusic");
}


void populateWorld(void) {
	

	for (int j = 0; j < 15; j++) {
		new Star;
	}

	new GameStart();

}

