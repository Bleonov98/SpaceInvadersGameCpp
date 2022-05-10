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
	if (_y > 3) {
		EraseObject();
		_y--;
	}
	
	if (_y == 3) {
		bulletGo = false;
		death = true;
	}
}

void Bullet::EnemyGunShot(bool &enemyBulletGo)
{
	if (_y <= 45) {
			EraseObject();
			_y++;
	}
	
	if (_y == 46) {
		enemyBulletGo = false;
		death = true;
	}
}

void Enemies::MoveEnemy(bool& worldIsRun)
{
	    EraseObject();
		
		enemyShotTimer = rand() % 10;

		if (tick < 20 && (loop == 1 || loop == 3 || loop == 5 || loop == 7)) {
			_x--;
		}

		if (tick < 20 && (loop == 2 || loop == 4 || loop == 6)) {
			_x++;
		}

		if (tick == 20) {
			loop++;
			_y += 4;
			tick = 0;
		}

		tick++;

		if (loop >= 7 && tick >= 20 && (!death)) { // if enemies go out from game map = they destroy n win;
			death = true;
			worldIsRun = false;
		}
}

void Wall::DrawObject()
{
		for (int i = 0; i < _height; i++)
		{
			for (int j = 0; j < _width; j++)
			{
				_wData->vBuf[_y + i][_x + j] = _symbol;
				if ((destroyWall[i][j].first == _x + j) && (destroyWall[i][j].second == _y + i))
				{
					_wData->vBuf[_y + i][_x + j] = 0x20;
				}
			}
		}
}
