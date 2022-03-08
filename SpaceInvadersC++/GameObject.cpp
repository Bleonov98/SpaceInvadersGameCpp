#include "GameObject.h"

void GameObject::SetPos(int x, int y)
{
	sprintf_s(coord, "%s%d;%dH", CSI, y, x);
	printf(coord);
}

void GameObject::DrawObject()
{
	_vBuf = ;
}

void GameObject::EraseObject()
{

}
