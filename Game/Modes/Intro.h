#ifndef INTRO_H
#define INTRO_H
#include <algorithm>
#include "Mode.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
class Intro : public Mode
{
    private:
    std::list<Sprite>* spriteListBuffer;
    cm::cVecArr_t* cVecArr;
    Mode* mPtr;
    sf::Text
    bool done = false;
    public:
    Intro(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, Mode* mptr);
    void run();
};
#endif // INTRO_H
