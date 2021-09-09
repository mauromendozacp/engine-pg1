#include "BaseGame/baseGame.h"

using namespace GL;

int main()
{
    BaseGame* game = new BaseGame();
    game->Play();
    if (game != nullptr)
    {
        game = nullptr;
        delete game;
    }
    return 0;
}