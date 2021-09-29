#include "Game/game.h"


using namespace GL;

int main()
{
    Game* game = new Game();
    game->Play();

    if (game != NULL)
    {
        game = NULL;
        delete game;
    }

    return 0;

}