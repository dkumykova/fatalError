// Implementation of Character - C

// Game Include
#include "Character_Java.h"
#include "Bullet.h"
#include "Player.h"

// Engine Include
#include <WorldManager.h>
#include <LogManager.h>

Character_Java::Character_Java() {

	//link to ship sprite
	setSprite("Character_Java");

	// Set Attack Related Damage 
	setAttackOneDamage(30);
	setAttackTwoDamage(60);
	setSuperDamage(100);
	setSuperCastTime(2); // 2 secs

	// Set Jump Speed
	setJumpSpeed(INITIAL_JUMP_SPEED);

	// Set Slowdowns (Character Unique) [30 means 1 sec] 
	// [Parameter 2 default as false. If true, means set countdown to slowdown at the same time]
	setHorizontalSlowdown(2, true);
	setJumpSlowdown(30, true);
	setDefenseSlowdown(300, true);
	setAttackOneSlowdown(30, true);
	setSuperAttackSlowdown(900, true); // 30 secs
	setSuperChanelingSlowdown(60, true);

	setIsHigherLevel(true); 

	//super_countdown = 10;
	//super = new LispSuper();
	//super->setActive(false);

}

void Character_Java::do_action_move_right() {
	move(1.5, 0);
}

void Character_Java::do_action_move_left() {
	move(-1.5, 0);
}

void Character_Java::do_action_jump() {
	setVelocity(df::Vector(0, getJumpSpeed()));
}

void Character_Java::do_action_defense() {
	//implementation in player character
}

void Character_Java::do_action_attack_1() {
	//normal - jump up and duplicate into 3 versions of self that land, but only 1 does damage - randomly chosen
	setVelocity(df::Vector(0, getJumpSpeed()));

	Vector p1 = Vector(getPosition().getX() + 20 * getPlayer()->getFacingRight(), getPosition().getY());
	Vector p2 = Vector(getPosition().getX() + 20 * getPlayer()->getFacingRight(), getPosition().getY());
	
	//getPlayer()->getOpponentPlayer().df::Vector(2 * getPlayer()->getFacingRight(), 3)
	clone1 = new JavaClone(p1);
	clone2 = new JavaClone(p2);
	clone1->setAffect(true);

	clone1->setVelocity(df::Vector(.6*getPlayer()->getFacingRight(), getJumpSpeed() + 1));
	clone1->setAcceleration(df::Vector(0, 0.5));
	clone2->setVelocity(df::Vector(.6*getPlayer()->getFacingRight() + 1, getJumpSpeed() + 2));
	clone2->setAcceleration(df::Vector(0, 0.5));
	
	
}

void Character_Java::do_action_super_attack() {
	// To do
	//stops all projectiles, clears all walls, stops enemy for attacking for 3 seconds
	//i want to use a countdown but might need to use a clock since i can't override eventhandler here

	LM.writeLog("Java super called");

	getPlayer()->getOpponentPlayer()->getCharacter()->getFrozen(3);
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "projectile" || p_o->getType() == "wall") {
			WM.markForDelete(p_o);
		}
	}
	//setSuperAttacking(false);
}



void Character_Java::flipSprite(PlayerCharacter::SpriteStatus sprite_status) {

	switch (sprite_status) {
	case PlayerCharacter::SpriteStatus::Original:
		setSprite("Character_Java");
		break;
	case PlayerCharacter::SpriteStatus::Flipped:
		setSprite("Character_Java_flip");
		break;
	case PlayerCharacter::SpriteStatus::Error_Attacking:
		setSprite("Character_Java_error");
		break;
	default:
		break;
	}
}

