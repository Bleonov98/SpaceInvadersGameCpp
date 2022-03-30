#include "GameObject.h"

void GameObject::DrawObject()
{
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			_wData->vBuf[_y + i][_x + j] = _symbol;
		}
	}
}

void GameObject::EraseObject()
{
	for (int i = 0; i < _height; i++)
	{
		for (int j = 0; j < _width; j++)
		{
			_wData->vBuf[_y + i][_x + j] = ' ';
		}
	}
}

void Bullet::MyGunShot()
{
	this_thread::sleep_for(milliseconds(1));

	while (_y >= 4) {

		DrawObject();
		
		Sleep(50);

		EraseObject();

		_y--;

	}

}
