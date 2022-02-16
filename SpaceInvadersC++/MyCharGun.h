#pragma once
#include "GameObject.h"
class MyCharGun: public GameObject
{
private:

public:

	MyCharGun(HANDLE hOut, int width, int height, int x, int y) : GameObject(hOut, width, height, x, y) {
	};

	void MoveMyGun();

	void RunGun();

};

