#include "stdfix.h"
#include "World.h"

int main()
{
    bool restart = false;
    do
    {
        World wd;
        wd.RunWorld(restart);

    } while (restart);

    return 0;
}
