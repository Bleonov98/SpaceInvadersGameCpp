#pragma once
#include "stdfix.h"

class Objects
{
private:

	char coord[50];

public:

	void SetPos(int x, int y);

	void DrawObj(int width, int height, int x, int y);

	void EraseObj(int width, int height, int x, int y);
};

class StaticObjects: public Objects 
{
private:

};

class DinamicObjects: public Objects 
{
private:

};
