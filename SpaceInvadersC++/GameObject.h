#pragma once
#include "BufferStruct.h"

class GameObject
{
public:

	int _width, _height, _x, _y;
	char _symbol;

	GameObject(wd* wData, int width, int height, int x, int y, char symbol) {
		_width = width, _height = height, _x = x, _y = y, _symbol = symbol;
		_wData = wData;

		DrawObject();
	};

protected:

	wd* _wData;

	void DrawObject();

	void EraseObject();
};











class StaticObjects: public GameObject 
{
private:



public:

};








class Enemies: public GameObject 
{
private:

public:

};








class Bullet : public GameObject
{

public:

	Bullet(wd* wData, int width, int height, int x, int y, char symbol) : GameObject(wData, width, height, x, y, symbol) {
	};

	void MyGunShot();

};
