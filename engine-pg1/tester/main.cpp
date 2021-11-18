#include "Game/game.h"

using namespace GameXD;

int main()
{
    Game* game = new Game();
    
    if (game != nullptr)
    {
        game->Play();
        delete game;
    }

    return 0;
}