#ifndef NEWMODE_H
#define NEWMODE_H
#include "Mode.h"
#include "../MouseReading.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <random>
class NewMode : public Mode
{
    private:
    bool done = false;
    int STAGE = 0;
    std::list<Sprite>::iterator sIt;
    std::list<Sprite>* spriteListBuffer;
    cm::cVecArr_t* cVecArr;
    MouseReading* mRead;
    bm::bStatusArr_t* bStatusArr;
    std::mt19937* randGen;
    public:
    NewMode(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, MouseReading* mread, bm::bStatusArr_t* bstatusarr,
            std::mt19937* randgen);
    void run();
};
#endif // NEWMODE_H


