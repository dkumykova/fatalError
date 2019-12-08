#include "TestingCharacter.h"
#include "WorldManager.h"
#include "GameOver.h"
#include <LogManager.h>

TestCharacter::TestCharacter(){
	//link to ship sprite
	setSprite("test character");

	// Set Type
	setType("TestCharacter");

	setIsPlayer1(true);

	// Set Starting Position
	df::Vector position(20, WM.getBoundary().getVertical() / 2);
	setPosition(position);
}

void TestCharacter::kbd(const df::EventKeyboard* p_key_event) {
	//LM.writeLog("Acceleration is now: %d", acceleration);
	//long int first_time = my_clock->delta();

	switch (p_key_event->getKey()) {
	case df::Keyboard::W:       // Jump
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			LM.writeLog("Key down W*");
			long int jump_time = my_clock->split() / 1000;

			if (jump_time < 1000) {
				//LM.writeLog("Too quick to jump!");
				LM.writeLog("%ld", jump_time);
				break;
			}

			my_clock->delta();
			setVelocity(df::Vector(0, -6));
			//LM.writeLog("Setting velocity to: %f, %f", getVelocity().getX(), getVelocity().getY());
			//if (on_ground) {
			//	LM.writeLog("Jump!");
			//	on_ground = false;
			//	//acceleration = -0.6;
			//setAcceleration(df::Vector(0, acceleration));
			//	//setVelocity(df::Vector(0, ));
			//	LM.writeLog("Velocity is now: %d, %d", getVelocity().getX(), getVelocity().getY());
			//	return;
			//}
			//LM.writeLog("Not on ground!");
		}
		break;
	case df::Keyboard::A:       // Left
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN) {
			move(-1, 0);
			return;
		}
		break;
	case df::Keyboard::S:       // Defend
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			//
			break;
	case df::Keyboard::D:       // Right
		if (p_key_event->getKeyboardAction() == df::KEY_DOWN)
			move(1, 0);
		break;

	case df::Keyboard::ESCAPE:  // quit
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			//new GameOver;
			break;
	case df::Keyboard::R:  // quit
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			new GameOver;
		break;
	case df::Keyboard::C: // attack 1
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			attack_1(true);
	case df::Keyboard::V: // attack 2
		if (p_key_event->getKeyboardAction() == df::KEY_PRESSED)
			attack_2(true);
		break;

	default: // Key not handled.
		return;
	};

	return;
}

void TestCharacter::collide(const df::EventCollision* p_c_event) {
	if ((p_c_event->getObject1()->getType() == "Platform") ||
		(p_c_event->getObject2()->getType() == "Platform")) {

		setVelocity(df::Vector()); //reset velocity to 0

	}
}

