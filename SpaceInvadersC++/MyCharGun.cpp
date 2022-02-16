#include "MyCharGun.h"

void MyCharGun::MoveMyGun()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (_x <= 146 - _width) {
			EraseObject();
			_x++;
			DrawObject();
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (_x > 2) {
			EraseObject();
			_x--;
			DrawObject();
		}
	}
}

void MyCharGun::RunGun()
{
	this_thread::sleep_for(1ms);
	while (true) {
		MoveMyGun();
		Sleep(30);
	}
}
