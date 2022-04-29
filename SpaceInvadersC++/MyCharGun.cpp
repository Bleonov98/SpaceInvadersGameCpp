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
