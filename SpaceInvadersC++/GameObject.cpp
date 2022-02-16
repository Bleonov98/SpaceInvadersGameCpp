#include "GameObject.h"

void GameObject::SetPos(int x, int y)
{
	sprintf_s(coord, "%s%d;%dH", CSI, y, x);
	printf(coord);
}

void GameObject::DrawObject()
{
	int buffSize = _width * _height;

	COORD mainPos, objSize;
	CHAR_INFO* objInfo = new CHAR_INFO[buffSize];

	SMALL_RECT objCrd;
	objCrd.Top = _y;
	objCrd.Bottom = _y + _height;
	objCrd.Left = _x;
	objCrd.Right = _x + _width;

	objSize.X = _width, objSize.Y = _height;

	mainPos.X = 0, mainPos.Y = 0;

	for (int i = 0; i < buffSize; i++)
	{
		objInfo[i].Char.UnicodeChar = '*';
		objInfo[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}

	WriteConsoleOutput(_hOut, objInfo, objSize, mainPos, &objCrd);
}

void GameObject::EraseObject()
{
	int buffSize = _width * _height;

	COORD mainPos, objSize;
	CHAR_INFO* objInfo = new CHAR_INFO[buffSize];

	SMALL_RECT objCrd;
	objCrd.Top = _y;
	objCrd.Bottom = _y + _height;
	objCrd.Left = _x;
	objCrd.Right = _x + _width;

	objSize.X = _width, objSize.Y = _height;

	mainPos.X = 0, mainPos.Y = 0;

	for (int i = 0; i < buffSize; i++)
	{
		objInfo[i].Char.UnicodeChar = ' ';
		objInfo[i].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	}

	WriteConsoleOutput(_hOut, objInfo, objSize, mainPos, &objCrd);
}
