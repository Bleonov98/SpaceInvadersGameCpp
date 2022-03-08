#pragma once
#include "stdfix.h"

class GameObject
{
private:

	char coord[50];

public:

	int _width, _height, _x, _y;

	vector <vector<char>> * _vBuf;

	GameObject() {}; // for tools

	GameObject(vector <vector<char>>& vBuf, int width, int height, int x, int y) {
		_width = width, _height = height, _x = x, _y = y;

		DrawObject();
	};

	void SetPos(int x, int y);

	void DrawObject();

	void EraseObject();
};

class StaticObjects: public GameObject 
{
private:



public:

};

class Bullet : public GameObject 
{

};

class Enemies: public GameObject 
{
private:

public:

};
