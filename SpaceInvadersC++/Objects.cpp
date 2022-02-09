#include "Objects.h"

void Objects::SetPos(int x, int y)
{
	sprintf_s(coord, "%s%d;%dH", CSI, y, x);
	printf(coord);
 }

void Objects::DrawObj(int width, int height, int x, int y)
{
	for (int i = 0; i < height; i++)
	{
		SetPos(x, y + i);
		for (int j = 0; j < width; j++)
		{
			cout << "#";
		}
	}
}

void Objects::EraseObj(int width, int height, int x, int y) {
	for (int i = 0; i < height; i++)
	{
		SetPos(x, y + i);
		for (int j = 0; j < width; j++)
		{
			cout << " ";
		}
	}
}