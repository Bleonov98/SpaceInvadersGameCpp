#include "MyCharGun.h"

void MyCharGun::MoveMyGun()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		if (_x <= 148 - _width) {
			EraseObject();
			_x++;
			DrawObject();
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		if (_x > 3) {
			EraseObject();
			_x--;
			DrawObject();
		}
	}
}

void MyCharGun::RunGun()
{
	while (true)
	{
		MoveMyGun();

	//		/*if (GetAsyncKeyState(VK_SPACE))
	//{
	//	Bullet* bullet = new Bullet(_wData, 1, 1, _x + _width / 2, _y - 1, '|');

	//	thread shot(&Bullet::MyGunShot, bullet);
	//	shot.detach();
	//}*/
		Sleep(30);
	}
}
