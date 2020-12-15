#ifndef MODE_H
#define MODE_H
#include "../../gfx/sprite.h"
#include "../Card.h"
#include "../Functions/CardManager.h"
#include <memory>
#include <deque>
#include <vector>
#include <list>
class Mode
{
    public:
    enum ModeName
    {
        INTROANIMATION, CHOOSEFIRSTCARD, MAINGAMESELECT, NEWMODE
    };
    virtual void run() = 0;
};
#endif // MODE_H
