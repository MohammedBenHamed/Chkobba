#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Card.h"
#include "Modes/Mode.h"
#include "Modes/NewMode.h"
#include "Functions/CardManager.h"
#include <list>
#include <iostream>
#include <deque>
#include <map>
#include <memory>
#include <type_traits>
#include <iostream>
#include <ctime>
class Game
{
    private:
    sf::Clock clock;
    sf::RenderWindow window;
    sf::Sprite background;
    sf::Texture b_pic;
    sf::Event event;
    Mode::ModeName modename = Mode::INTROANIMATION;
    std::list<Sprite> spriteListBuffer;
    cm::cVecArr_t cVecArr;
    std::unique_ptr<Mode> mode = nullptr;
    sf::Font font;
    sf::Text text;
    void modeRun();
    void updateSprites();
    public:
    Game();
    void run();
};
#endif // GAME_H
