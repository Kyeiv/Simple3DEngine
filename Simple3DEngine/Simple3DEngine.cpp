#include "Engine.h"

int main()
{
	Engine demo;
	if (demo.ConstructConsole(256, 240, 4, 4))
		demo.Start();
    return 0;
}

