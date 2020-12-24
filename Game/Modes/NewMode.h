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
    int done = 0;
    int STAGE = 0;
    Sprite sprite;
    std::list<Sprite>* spriteListBuffer;
    cm::cVecArr_t* cVecArr;
    public:
    NewMode(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr);
    void run();
};
#endif // NEWMODE_H


