#pragma once
#include "stdfix.h"

class GameObject
{
private:

	

public:

	GameObject() {};

	GameObject(int width, int height) {

		vector<vector<char>> obj;
		obj.resize(height);
		for (int i = 0; i < height; i++)
		{
			obj.resize(width);
		}

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				obj[i][j] = '#';
			}
		}
	};

	void SpawnObj();

};

class StaticObjects: public GameObject 
{
private:

public:

};

class Characters: public GameObject 
{
private:

	vector<pair<int, int>> dir;
	vector<pair<int, int>> bullet;

public:

	void MoveChar(int width, int height, int x, int y);

	void GunShot(int x, int y);

};
