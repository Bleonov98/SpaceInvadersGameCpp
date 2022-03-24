#include "World.h"

void World::SetPos(int x, int y)
{
	sprintf_s(coord, "%s%d;%dH", CSI, y, x);
	printf(coord);
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
	CreateWorld();

	MyCharGun myGun(&wData, 5, 3, COLS / 2 - 2, ROWS - 3, '*'); // Player cannon size and position
	thread runGun(&MyCharGun::RunGun, myGun);
	runGun.detach();

	SetPos(0, 0);

	while (worldIsRun)
	{
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
		cout << flush;
		memcpy(prevBuf, wData.vBuf, ROWS * COLS);
	}

	printf(CSI "?1049l"); // enable main buffer
}

