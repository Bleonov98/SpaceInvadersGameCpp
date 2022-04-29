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

void GameObject::ObjectDeath()
{
	EraseObject();

	cout << "X";

}

void Bullet::MyGunShot(bool &bulletGo)
{
	while (_y >= 0 && death != true) {
		if (ready)
		{
			this_thread::sleep_for(milliseconds(5));
			EraseObject();
			_y--;
		}
	}

	bulletGo = false;
}

void Enemies::MoveEnemy()
{
	mtx.lock();
	int tick = 1;
	loop = 0;
	while (loop != 4 && death != true) {
		while (tick != 20 && death != true) {
			if (ready) {
				this_thread::sleep_for(milliseconds(100));
				EraseObject();
				_x--;
				this_thread::sleep_for(milliseconds(300 - loop * 70));
				tick++;
			}
		}

		if (death != true) {
			this_thread::sleep_for(milliseconds(100));
			EraseObject();
			_y += 4;
			this_thread::sleep_for(milliseconds(300 - loop * 70));
			tick++;
		}
		

		while (tick != 43 && death != true) {
			if (ready) {
				this_thread::sleep_for(milliseconds(100));
				EraseObject();
				_x++;
				this_thread::sleep_for(milliseconds(300 - loop * 70));
				tick++;
			}
		}

		if (death != true) {
			this_thread::sleep_for(milliseconds(100));
			EraseObject();
			_y += 4;
			this_thread::sleep_for(milliseconds(300 - loop * 70));
			tick++;
		}
				
		tick = 1;
		loop++;
	}

	this_thread::sleep_for(milliseconds(50));
	EraseObject();
	
	mtx.unlock();
}
