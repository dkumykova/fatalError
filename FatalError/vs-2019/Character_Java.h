#pragma once
#include "PlayerCharacter.h"
#include "LispSuper.h"


class Character_Java : public PlayerCharacter {
private:
	LispSuper* super;

public:
	Character_Java();

	// Move Related
	void do_action_move_right();
	void do_action_move_left();
	void do_action_jump();
	void do_action_defense();
	void do_action_attack_1();
	void do_action_super_attack();


	// Sprite Related
	void flipSprite(PlayerCharacter::SpriteStatus sprite_status);
};
