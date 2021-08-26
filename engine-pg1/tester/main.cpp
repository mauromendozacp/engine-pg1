#include "BaseGame/baseGame.h"

//using namespace GL;

int main()
{
    GL::BaseGame* game = new GL::BaseGame();
    game->Play();
    if (game != nullptr)
    {
        game = nullptr;
        delete game;
    }
    return 0;
}