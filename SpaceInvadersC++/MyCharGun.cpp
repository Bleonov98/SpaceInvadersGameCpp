#include "MyCharGun.h"

void MyCharGun::MoveMyGun()
{
		if (GetAsyncKeyState(VK_RIGHT)) {
			if (_x <= 148 - _width) {
				EraseObject();
				_x++;
			}
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			if (_x > 3) {
				EraseObject();
				_x--;
			}
		}
}

void MyCharGun::myGunDeath(bool &worldIsRun)
{
	if (death && lifes > 0) {

		Sleep(2000);

		lifes--;

		if (lifes > 0) {
			death = false;
		}
		else death = true;
	}

	if (death) {
		worldIsRun = false;
	}
}
