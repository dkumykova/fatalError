#pragma once
#include "PlayerCharacter.h"


class Character_C : public PlayerCharacter {


public:
	Character_C();
	void attack_1();
	void attack_2();
	void specialAttack();
	void moveRight();
	void moveLeft();
	void jump();
	void flipSprite(PlayerCharacter::SpriteStatus sprite_status);
};