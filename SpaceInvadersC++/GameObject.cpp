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


void Bullet::MyGunShot(bool &bulletGo)
{
	death = false;
	while (_y >= 3 && death != true) {
		if (ready)
		{
			EraseObject();
			_y--;
			DrawObject();
			ready = false;
		}
	}

	if (death != true) {
		death = true;
	}
	
	bulletGo = false;
}

void Bullet::EnemyGunShot(bool &enemyBulletGo)
{
	death = false;
	while (_y <= 45 && death != true) {
		if (ready)
		{
			EraseObject();
			_y++;
			DrawObject();
			ready = false;
			this_thread::sleep_for(milliseconds(20));
		}
	}

	enemyBulletGo = false;
	death = true;
}

void Enemies::MoveEnemy()
{
	    EraseObject();
		
		enemyShotTimer = rand() % 10;

		if (tick < 20 && (loop == 1 || loop == 3 || loop == 5 || loop == 7)) {
			_x--;
		}

		if (tick < 20 && (loop == 2 || loop == 4 || loop == 6 || loop == 8)) {
			_x++;
		}

		if (tick == 20) {
			loop++;
			_y += 4;
			tick = 0;
		}

		tick++;

		if (loop >= 8 && tick >= 20 && (!death)) {
			death = true;
		}
}
