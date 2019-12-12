#pragma once
#include <object.h>
#include "Character_Python.h"

class Character_Pip : df::Object {

private:
	Character_Python* p_master;

public:
	Character_Pip(Character_Python* master);
	int eventHandler(const df::Event* p_e); // Event Hanlder
};