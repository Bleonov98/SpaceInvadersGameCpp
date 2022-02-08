#include "World.h"

void World::RunWorld()
{
	term.Terminal();
	term.SetScreenSize();

	printf(CSI "?1049h");
	printf(CSI "?25l");

	while (true)
	{

	}

	printf(CSI "?1049l");
}
