#include "Game.h"

#include <iostream>
#include <fstream>
#ifdef _DEBUG
int main()
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine, int nCmdShow)
#endif
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    try {
        std::fstream file;
        file.open("hola.txt");

        Game game;
        if (game.init("MOOD"))
            game.run();
    }
    catch (std::exception & e) {
        std::cout << "ERROR: " << e.what();
    }

	return 0;
}
