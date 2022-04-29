#pragma once
#include "BufferStruct.h"

class GameObject
{
public:

	mutex mtx;
	
	int _width, _height, _x, _y;
	char _symbol;
	bool ready, death = false;
	

	GameObject(wd* wData, int width, int height, int x, int y, char symbol) {
		_width = width, _height = height, _x = x, _y = y, _symbol = symbol;
		_wData = wData;
	};

	void DrawObject();

	void EraseObject();

	void ObjectDeath();

protected:

	wd* _wData;
};











class StaticObjects: public GameObject 
{
private:



public:

};








class Enemies: public GameObject 
{

public:
	int loop;

	Enemies(wd* wData, int width, int height, int x, int y, char symbol) : GameObject(wData, width, height, x, y, symbol) {
	};

	void MoveEnemy();

};








class Bullet : public GameObject
{

public:

	Bullet(wd* wData, int width, int height, int x, int y, char symbol) : GameObject(wData, width, height, x, y, symbol) {
	};

	void MyGunShot(bool &bulletGo);

};
