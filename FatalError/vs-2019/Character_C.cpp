// Implementation of Character - C

// Game Include
#include "Character_C.h"
#include "Bullet.h"
#include "Player.h"

// Engine Include
#include <WorldManager.h>

Character_C::Character_C() {

	//link to ship sprite
	setSprite("test character");

	// Set Damage 
	setAttackOneDamage(30);
	setAttackTwoDamage(60);
}

void Character_C::attack_1(){
	Bullet* p = new Bullet(Vector(getPosition().getX() + 20 * getPlayer()->getFacingRight(), getPosition().getY()));
	p->setVelocity(df::Vector(0.2 * getPlayer()->getFacingRight(), 0));
}

void Character_C::attack_2(){
	Bullet* p = new Bullet(Vector(getPosition().getX() + 20 * getPlayer()->getFacingRight(), getPosition().getY()));
	p->setVelocity(df::Vector(2 * getPlayer()->getFacingRight(), 0));
}

void Character_C::specialAttack(){

}

void Character_C::moveRight(){
	move(1.5,0);
}

void Character_C::moveLeft(){
	move(-1.5, 0);
}

void Character_C::jump(){
	setVelocity(df::Vector(0, JUMP_VELOCITY));
}
