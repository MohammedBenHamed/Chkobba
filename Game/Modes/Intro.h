#ifndef INTRO_H
#define INTRO_H
#include <algorithm>
#include "Mode.h"
#include "../Game.h"
#include "../MouseReading.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>
class Intro : public Mode
{
    private:
    enum
    {
        INTRO_ANIM, CHOOSECARD, MOVECARDSBACK, KEEPORNOT, CHOOSEOPTION, DEALCARDS, DRAWBUTTON
    } modeStage = INTRO_ANIM;
    std::list<Sprite>* spriteListBuffer;
    cm::cVecArr_t* cVecArr;
    Mode::ModeName* mPtr;
    sf::Text* tPtr;
    bool askForInput = false;
    MouseReading* mRead;
    std::list<Sprite>::iterator selectedCardSprite;
    bm::buttonType buttonClicked; // used for DEALCARDS
    std::array<cm::Deck,3> decksToDeal = {cm::HMNHAND, cm::CPUHAND, cm::TABLE}; // used for DEALCARDS

    bm::bStatusArr_t* bStatusArr;
    std::mt19937* randGen;
    public:
    Intro(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, Mode::ModeName* mptr, sf::Text* tptr,
    MouseReading* mread, bm::bStatusArr_t* bstatusarr, std::mt19937* randgen);
    void run();
};
#endif // INTRO_H
