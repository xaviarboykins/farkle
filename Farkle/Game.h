#pragma once

#include "Player.h"

class Game
{
private:
	Player player;

	void Greet();
	void LoadMenu();
	void ShowRules();
	void Farkle();

public:
	void Launch();
};

