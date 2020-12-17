#ifndef CARDMANAGER_H
#define CARDMANAGER_H
#include <array>
#include <vector>
#include <memory>
#include <utility>
#include <tuple>
#include <list>
#include <functional>
#include "../../gfx/sprite.h"
#include "../Card.h"
#include <algorithm>
namespace cm
{
    constexpr std::array<int,14> xConstants = {300,420,540,353,486,60,180,300,420,540,108,236,364,492};
    // x coordinates that cards take when moving to CPUHAND, HMNHAND and TABLE "deck"s.
    // first 3 - HAND positions when size = 1 or 3
    // 4 and 5 - HAND positions when size = 2
    // 60 to 640 - TABLE positions when size%5 + 1 = 5,3,1
    // 108 to end - TABLE positions when size%5 + 1 = 2,4
    constexpr std::array<uint8_t,3> xHANDStartArr = {1,3,0};
    // starting positions for HAND locations
    constexpr std::array<uint8_t,5> xTABLEStartArr = {7,11,6,10,5};
    // starting positions for TABLE locations
    constexpr int Y_HANDCPU = 20;
    constexpr int Y_HANDHMN = 460;
    constexpr int Y_TABLEUPPER = 170;
    constexpr int Y_TABLEMID   = 240;
    constexpr int Y_TABLELOWER = 310;


    typedef std::array<std::vector<Card>,6> cVecArr_t;
    enum Deck // index of the arrays in cVecArr_t
    {
        DECK, TABLE, HMNHAND, HMNPILE, CPUHAND, CPUPILE
    };
    void addCard(Card c, Deck d, float x, float y, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void removeCard(Card c, Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void flipCard(Card c, Deck d, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void instantFlipCard(Card c, Deck d, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void moveCard(Card c, Deck d, float x, float y, float spd, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void moveCardToHome(Card c, Deck from, Deck to, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    bool cardUpdating(Card c, Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    //
}

#endif // CARDMANAGER_H
