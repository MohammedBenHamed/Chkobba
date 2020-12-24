#include <SFML/Graphics.hpp>
#include "Game/Game.h"
int main()
{
    Game game;
    game.run();
    std::cout << "Game successfully ended\n";
    return 0;
}
