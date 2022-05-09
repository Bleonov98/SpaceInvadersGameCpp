#pragma once
#include "GameObject.h"

class MyCharGun: public GameObject
{
public:

	int lifes = 3;

	MyCharGun(wd* wData, int width, int height, int x, int y, char symbol) : GameObject(wData, width, height, x, y, symbol) {
	};

	void MoveMyGun();

	void myGunDeath(bool& worldIsRun);
	
};

