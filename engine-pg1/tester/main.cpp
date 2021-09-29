#include "Game/game.h"


using namespace GL;

int main()
{
    Game* game = new Game();
    
    if (game != NULL)
    {
        game->Play();
        delete game;
    }

    return 0;

}