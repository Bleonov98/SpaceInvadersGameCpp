#pragma once
#include "BufferStruct.h"

class GameObject
{
public:
	int _width, _height, _x, _y;
	char _symbol;
	bool ready, death = false;
	

	GameObject(wd* wData, int width, int height, int x, int y, char symbol) {
		_width = width, _height = height, _x = x, _y = y, _symbol = symbol;
		_wData = wData;
	};

	virtual void DrawObject();

	void EraseObject();

	virtual ~GameObject() {
		delete this;
	};

protected:

	wd* _wData;
};




class Wall: public GameObject 
{
public:

	int parts = _width * _height;
	vector <vector<pair<int, int>>> destroyWall;

	Wall(wd* wData, int width, int height, int x, int y, char symbol) : GameObject(wData, width, height, x, y, symbol) {
	};

	void DrawObject();
};



class Enemies: public GameObject 
{

public:
	int tick = 1;
	int loop = 1;
	int enemyShotTimer = rand() % 10;
	bool enemyBulletGo = false;

	Enemies(wd* wData, int width, int height, int x, int y, char symbol) : GameObject(wData, width, height, x, y, symbol) {
	};

	void MoveEnemy(bool& worldIsRun);

};


class Bullet : public GameObject
{

public:

	Bullet(wd* wData, int width, int height, int x, int y, char symbol) : GameObject(wData, width, height, x, y, symbol) {
	};

	void MyGunShot(bool &bulletGo);

	void EnemyGunShot(bool &enemyBulletGo);

};
