#include "World.h"

void World::SetPos(int x, int y)
{
	sprintf_s(coord, "%s%d;%dH", CSI, y, x);
	printf(coord);
}

void World::HotKeys()
{
}

void World::DrawArea()
{
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleOutputCP(CP_UTF8);

	// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(IDR_TEXT1), L"TEXT");

	if (hResource)
	{
		HGLOBAL hLoadedResource = LoadResource(hInstance, hResource);

		if (hLoadedResource)
		{
			LPCSTR area = (LPCSTR)LockResource(hLoadedResource);

			if (area)
			{
				DWORD dwResourceSize = SizeofResource(hInstance, hResource);

				if (0 != dwResourceSize)
				{
					for (int i = 0; i < strnlen(area, 8915); i++) {
						std::cout << area[i];
					}
				}
			}
		}
	}

	setvbuf(stdout, NULL, _IONBF, 0);
}

void World::CreateWorld() {

	term.Terminal();  // Set virtual terminal settings
	term.SetScreenSize();

	printf(CSI "?1049h"); // enable alt buffer
	printf(CSI "?25l"); // hide cursor blinking

	DrawArea();
}

void World::RunWorld()
{
	srand(time(NULL));
	CreateWorld();

	MyCharGun* myGun = new MyCharGun(&wData, 5, 3, COLS / 2 - 2, ROWS - 3, '*');		// Player cannon size and position
	objVect.allKnownObjects.push_back(myGun);

	for (int i = 1; i < 6; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			enemy = new Enemies(&wData, 3, 2, 25 * i, 4 * j - 1, '#');;

			objVect.allKnownObjects.push_back(enemy);
			enemyList.push_back(enemy);
		}
	}

	SetPos(0, 0);

	while (worldIsRun)
	{	
     	if (tick % level == 0) {  	   		
			for (int i = 0; i < enemyList.size(); i++)
			{
				if (!enemyList[i]->death) {
					enemyList[i]->MoveEnemy();
				}
			}
		}
		// Move Enemies

		myGun->MoveMyGun(); // Move my Gun

		if (GetAsyncKeyState(VK_SPACE) && (!bulletGo))
		{
			bulletGo = true;

			Bullet* myBullet = new Bullet(&wData, 1, 1, myGun->_x + myGun->_width / 2, myGun->_y - 1, '|');

			thread shot(&Bullet::MyGunShot, myBullet, ref(bulletGo));
			shot.detach();

			myBulletList.push_back(myBullet);
			objVect.allKnownObjects.push_back(myBullet);
		}
		// myBulletGo settings

		if (enemyBulletList.empty() && (!enemyList.empty()))
		{
			int containerForBullets = 0;
			for (int i = 0; i < enemyList.size(); i++)
			{
				if ((enemyList[i]->enemyShotTimer == 5) && (!enemyList[i]->enemyBulletGo)) {

					enemyList[i]->enemyBulletGo = true;

					containerForBullets = i;

					break;
				}
			}
			Bullet* enemyBullet = new Bullet(&wData, 1, 1, enemyList[containerForBullets]->_x + enemyList[containerForBullets]->_width / 2, enemyList[containerForBullets]->_y + 2, '0');

			objVect.allKnownObjects.push_back(enemyBullet);
			enemyBulletList.push_back(enemyBullet);

			thread enemyGunShot(&Bullet::EnemyGunShot, enemyBullet, ref(enemyList[containerForBullets]->enemyBulletGo));
			enemyGunShot.detach();
		}
		// enemyBulletGo settings

        if ((!myBulletList.empty()) && (!enemyList.empty())) {

 		for (int i = 0; i < enemyList.size(); i++) {
				if (((enemyList[i]->_x == myBulletList.back()->_x) &&
					(enemyList[i]->_y == myBulletList.back()->_y)) ||
					((enemyList[i]->_x + 1 == myBulletList.back()->_x) &&
						(enemyList[i]->_y + 1 == myBulletList.back()->_y)) ||
					((enemyList[i]->_x + 2 == myBulletList.back()->_x) &&
						(enemyList[i]->_y + 2 == myBulletList.back()->_y)))
				{
					enemyList[i]->death = true;
					enemyList.erase(enemyList.begin() + i);

					myBulletList.back()->death = true;

					break;
				}

			}
		}
		// enemy die settings

		if (!myBulletList.empty()) {
			for (int i = 0; i < myBulletList.size(); i++)
			{
				if (myBulletList[i]->death == true) {
					myBulletList.erase(myBulletList.begin() + i);
				}
				else myBulletList[i]->ready = true;
			}
		}
		// myBullet vector erase and myBullet object go

		if (!enemyBulletList.empty()) {
			for (int i = 0; i < enemyBulletList.size(); i++)
			{
				if (enemyBulletList[i]->death == true) {
					enemyBulletList.erase(enemyBulletList.begin() + i);
				}
				else enemyBulletList[i]->ready = true;
			}
		}
		// enemyBullet vector erase and enemyBullet object go


		for (int i = 0; i < objVect.allKnownObjects.size(); i++)
		{
			if (objVect.allKnownObjects[i]->death == true) {
				objVect.allKnownObjects[i]->EraseObject();
				objVect.allKnownObjects.erase(objVect.allKnownObjects.begin() + i);
			}
		}
		// All objects vector settings (if some object was died = erase from vect;


		for (int i = 0; i < objVect.allKnownObjects.size() - enemyBulletList.size() - myBulletList.size(); i++)
		{
			objVect.allKnownObjects[i]->DrawObject();
		}
		// Draw all moving object (except threads)

		for (int i = 0; i < objVect.allKnownObjects.size(); i++)
		{
			while ((objVect.allKnownObjects[i]->ready) && (!objVect.allKnownObjects[i]->death)) {}
		}
		// waiting for all objects drawing func (ready and alive)

		
		for (int y = 0; y < ROWS; y++)
		{
			for (int x = 0; x < COLS; x++)
			{
				if (prevBuf[y][x] == wData.vBuf[y][x])
				{
					continue;
				}
				SetPos(x, y);
				cout << wData.vBuf[y][x];
			}
		}

		memcpy(prevBuf, wData.vBuf, ROWS * COLS);
		// double buffering output function

		Sleep(15);

		tick++;
	}

	printf(CSI "?1049l"); // enable main buffer
}
