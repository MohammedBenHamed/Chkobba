#ifndef CARDMANAGER_H
#define CARDMANAGER_H
#include <deque>
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
}

#endif // CARDMANAGER_H
