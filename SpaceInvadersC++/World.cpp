#include "World.h"

void World::SetPos(int x, int y)
{
	sprintf_s(coord, "%s%d;%dH", CSI, y, x);
	printf(coord);
}

void World::DrawInfo()
{
	SetPos(17, 52);
	cout << score;
	SetPos(16, 53);
	cout << enemyList.size();
}

void World::EraseLife(int lifes)
{
	for (int height = 0; height < 4; height++)
	{
		SetPos(42 + (10 * lifes), 51 + height);
		for (int width = 0; width < 5; width++)
		{
			cout << " ";
		}
	}
}

void World::HotKeys()
{
	while (worldIsRun) {
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			worldIsRun = false;
		}
 		if (GetAsyncKeyState(0x50)) {
			pause = !pause;
		}
	}
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

void World::RunWorld(bool &restart)
{
	srand(time(NULL));
	CreateWorld();

	thread hotKeys([&]
		{ HotKeys(); }
	);
	hotKeys.detach();

	int level = 1;
	int tick = 1;
	score = 0;

		MyCharGun* myGun = new MyCharGun(&wData, 5, 3, COLS / 2 - 2, ROWS - 3, '*');		// Player cannon size and position
		objVect.allKnownObjects.push_back(myGun);

		for (int i = 0; i < 3; i++)
		{
			wall = new Wall(&wData, 10, 3, (50 * (i + 1)) - 30, ROWS - 10, '=');

			wallList.push_back(wall);
			objVect.allKnownObjects.push_back(wall);

			wallList[i]->destroyWall.resize(wallList[i]->_height);

			for (int height = 0; height < wallList[i]->_height; height++)
			{
				wallList[i]->destroyWall[height].resize(wallList[i]->_width);
			}
		}

		SetPos(0, 0); // set cursor position to x, y = 0 for drawing from default position;
		
     	while (worldIsRun) 
		{
			if (enemyList.empty()) {
				for (int i = 1; i < 6; i++)
				{
					for (int j = 1; j < 4; j++)
					{
						enemy = new Enemies(&wData, 3, 2, 25 * i, 4 * j - 1, '#');

						objVect.allKnownObjects.push_back(enemy);
						enemyList.push_back(enemy);
					}
				}
			}
			// enemies size and position

			while (pause) {}

			if (tick % (11 - level) == 0) {
				for (int i = 0; i < enemyList.size(); i++)
				{
					if (!enemyList[i]->death) {
						enemyList[i]->MoveEnemy(worldIsRun);
					}
				}

				if (enemyList.empty()) {
					for (int i = 1; i < 6; i++)
					{
						for (int j = 1; j < 4; j++)
						{
							enemy = new Enemies(&wData, 3, 2, 25 * i, 4 * j - 1, '#');

							objVect.allKnownObjects.push_back(enemy);
							enemyList.push_back(enemy);
						}
					}
					level -= 1;
				}
			}
			// Move and spawn Enemies

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
				enemyBullet = new Bullet(&wData, 1, 1, enemyList[containerForBullets]->_x + enemyList[containerForBullets]->_width / 2, enemyList[containerForBullets]->_y + 2, '0');

				objVect.allKnownObjects.push_back(enemyBullet);
				enemyBulletList.push_back(enemyBullet);

				thread enemyGunShot(&Bullet::EnemyGunShot, enemyBullet, ref(enemyList[containerForBullets]->enemyBulletGo));
				enemyGunShot.detach();
			}
			// enemyBulletGo settings

			if ((!myBulletList.empty()) && (!enemyList.empty())) {
				bool enemyDieBreak = false;
				for (int i = 0; i < enemyList.size(); i++) {

					for (int height = 0; height < enemyList[i]->_height; height++)
					{
						for (int width = 0; width < enemyList[i]->_width; width++)
						{
							if ((enemyList[i]->_x + width == myBulletList.back()->_x) && (enemyList[i]->_y + height == myBulletList.back()->_y))
							{
								enemyList[i]->death = true;
								enemyList.erase(enemyList.begin() + i);

								myBulletList.back()->death = true;

								score += 20;

								enemyDieBreak = true;
								break;
							}
						}
						if (enemyDieBreak) break;
					}
					if (enemyDieBreak) break;
				}
			}
			// enemy die settings

			if ((!myGun->death) && (!enemyBulletList.empty())) {
				for (int i = 0; i < myGun->_height; i++)
				{
					for (int j = 0; j < myGun->_width; j++)
					{
						if ((myGun->_x + j == enemyBullet->_x) && (myGun->_y + i == enemyBullet->_y))
						{
							myGun->death = true;
							myGun->myGunDeath(worldIsRun);

							enemyBullet->death = true;
							enemyBulletList.erase(enemyBulletList.begin());

							EraseLife(myGun->lifes);

							break;
						}
					}
					if (myGun->death) {
						break;
					}
				}
			}
			//myGun die settings

			if (!wallList.empty()) {
   				for (int i = 0; i < wallList.size(); i++)
				{
					for (int height = 0; height < wallList[i]->_height; height++)
					{
						for (int width = 0; width < wallList[i]->_width; width++)
						{
							if ((!myBulletList.empty()) && ((wallList[i]->_x + width == myBulletList.back()->_x) && (wallList[i]->_y + height == myBulletList.back()->_y))
								&& (wallList[i]->destroyWall[height][width].first != myBulletList.back()->_x) && (wallList[i]->destroyWall[height][width].second != myBulletList.back()->_y))
							{

								wallList[i]->destroyWall[height][width].first = wallList[i]->_x + width;
								wallList[i]->destroyWall[height][width].second = wallList[i]->_y + height;

								wallList[i]->parts--; 

								myBulletList.back()->death = true;
							}
							else if ((!enemyBulletList.empty()) && ((wallList[i]->_x + width == enemyBulletList.back()->_x) && (wallList[i]->_y + height == enemyBulletList.back()->_y))
								&& (wallList[i]->destroyWall[height][width].first != enemyBulletList.back()->_x) && (wallList[i]->destroyWall[height][width].second != enemyBulletList.back()->_y)) {
		
								wallList[i]->destroyWall[height][width].first = wallList[i]->_x + width;
								wallList[i]->destroyWall[height][width].second = wallList[i]->_y + height;

								wallList[i]->parts--;

								enemyBulletList.back()->death = true;
							}
						}
					}

					if (wallList[i]->parts == 0) {
						wallList[i]->death = true;
						wallList.erase(wallList.begin() + i);
					}
				}
			}
			//wall destroy settings

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

			if (!enemyList.empty()) {
				for (int i = 0; i < enemyList.size(); i++)
				{
					if (enemyList[i]->death == true) {
						enemyList.erase(enemyList.begin() + i);
					}
				}
			}
			// enemyList vector erase if the object is dead

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

			DrawInfo();

			if (objVect.allKnownObjects.size() <= 2) {
				Sleep(25);
			}
			else Sleep(15);

			tick++;
		}

		if (!objVect.allKnownObjects.empty()) {
			for (int i = 0; i < objVect.allKnownObjects.size(); i++)
			{
				objVect.allKnownObjects[i]->death = true;
				objVect.allKnownObjects[i] = NULL;
			}
		}

		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				wData.vBuf[i][j] = 0x20;
			}
		}

		enemyList.clear();
		wallList.clear();
		objVect.allKnownObjects.clear();
		myBulletList.clear();
		enemyBulletList.clear();

		SetPos(70, 22);
		cout << "GAME OVER";
		SetPos(70, 24);
		cout << "SCORE:" << score;
		SetPos(70, 25);
		cout << "LEVEL: " << level << "/10";
		SetPos(65, 28);
		cout << "PRESS ENTER TO RESTART";
		SetPos(65, 29);
		cout << "PRESS ESC TO EXIT";

		bool pressed = false;
		do {
			if (GetAsyncKeyState(VK_RETURN)) {
				restart = true;
				pressed = true;
			}
			else if (GetAsyncKeyState(VK_ESCAPE)) {
				restart = false;
				pressed = true;
			}
		} while (!pressed);
		

	 printf(CSI "?1049l"); // enable main buffer
}
