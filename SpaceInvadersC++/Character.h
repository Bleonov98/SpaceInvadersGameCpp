#pragma once
#include "stdfix.h"

class Character
{
private:

	char coord[50];

public:

	void SetPos(int x, int y);

	void DrawChar(int width, int height, int x, int y);

};

