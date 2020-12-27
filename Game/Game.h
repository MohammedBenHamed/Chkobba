#ifndef GAME_H
#define GAME_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Card.h"
#include "Modes/Mode.h"
#include "Modes/NewMode.h"
#include "Modes/Intro.h"
#include "Functions/CardManager.h"
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <deque>
#include <set>
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
    Mode::ModeName modename = Mode::INTRO;

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
    struct compFunc
    {
        bool operator()(const std::list<Sprite>::iterator &lhs, const std::list<Sprite>::iterator &rhs) const;
    };
    private:
    std::multiset<std::list<Sprite>::iterator,compFunc> itSet; // Contains iterators whose order will be used when drawing
    std::ofstream file;
    unsigned long long int frameCount = 0;
};
#endif // GAME_H
