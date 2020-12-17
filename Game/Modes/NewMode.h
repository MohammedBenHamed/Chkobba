#ifndef NEWMODE_H
#define NEWMODE_H
#include "Mode.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
class NewMode : public Mode
{
    private:
    bool done = 0;
    bool done2 = 0;
    bool done3 = 0;
    bool done4 = 0;
    bool done5 = 0;
    bool done6 = 0;
    bool done7 = 0;
    bool done8 = 0;
    bool done9 = 0;
    Sprite sprite;
    std::list<Sprite>* spriteListBuffer;
    cm::cVecArr_t* cVecArr;
    public:
    NewMode(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr);
    void run();
};
#endif // NEWMODE_H


