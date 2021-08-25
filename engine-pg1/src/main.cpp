#include "exports.h"
#include "BaseGame/baseGame.h"

using namespace GL;

int main(void)
{
    BaseGame* game = new BaseGame();
    game->Play();
    return 0;
}