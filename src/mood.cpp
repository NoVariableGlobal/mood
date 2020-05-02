#include "Game.h"

#include <ctime>
#include <iostream>
#ifdef _DEBUG
int main()
#else
#include <windows.h>
int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lmCmdLine,
                   int nCmdShow)
#endif
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    try {
        srand(time(nullptr));
        Game game;
        if (game.init("mainmenu", "TaharezLook", "TaharezLook.scheme",
                      "TaharezLook/MouseTarget", "DejaVuSans-14"))
            game.run();
    } catch (std::exception& e) {
        std::cout << "\n"
                  << "================"
                  << "\n"
                  << "ERROR: " << e.what() << "\n"
                  << "================"
                  << "\n";
    }

    return 0;
}
