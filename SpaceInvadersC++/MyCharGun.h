#pragma once
#include "GameObject.h"

class MyCharGun: public GameObject
{
public:

	MyCharGun(wd* wData, int width, int height, int x, int y, char symbol) : GameObject(wData, width, height, x, y, symbol) {
	};

	void MoveMyGun();
};

