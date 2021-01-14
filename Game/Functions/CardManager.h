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
//#include "CMHelperFunctions.h"
#include "CMMacros.h"
#include <algorithm>
#include <random>

#include <iterator>
namespace cm
{
    constexpr std::array<uint8_t,3> xHANDStartArr = {1,3,0};
    // starting positions for HAND locations
    constexpr std::array<uint8_t,5> xTABLEStartArr = {7,11,6,10,5};
    // starting positions for TABLE locations
    constexpr std::array<int,3> xHandOddConsts   = {300,420,540};
    constexpr std::array<int,2> xHandEvenConsts  = {353,486};
    constexpr std::array<int,5> xTableOddConsts  = {60,180,300,420,540};
    constexpr std::array<int,4> xTableEvenConsts = {108,236,364,492};

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
    void alterCardPriority(Card c, Deck d, int8_t priority, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void flipCard(Card c, Deck d, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void instantFlipCard(Card c, Deck d, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void moveCard(Card c, Deck d, float x, float y, float spd, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void moveCard(std::list<Sprite>::iterator spriteIt, float x, float y, float spd, unsigned int wait, std::list<Sprite>* sBuffer);
    void moveCardToHome(Card c, Deck from, Deck to, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    // Must check if card from "from" is not moving to move card to a certain home
    bool cardUpdating(Card c, Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    bool deckUpdating(Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    bool spriteIsCard(std::list<Sprite>::iterator spriteIt, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    std::pair<Card,Deck> getCardFromSprite(std::list<Sprite>::iterator cIt, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
    void shuffleCards(std::mt19937* randGen, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
}

#endif // CARDMANAGER_H
