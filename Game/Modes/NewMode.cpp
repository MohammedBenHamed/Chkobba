#include "NewMode.h"

NewMode::NewMode(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, MouseReading* mread,
                 bm::bStatusArr_t* bstatusarr, std::mt19937* randgen)
: spriteListBuffer(spritelistbuffer), cVecArr(cvecarr), mRead(mread), bStatusArr(bstatusarr), randGen(randgen)
{
     for (int i = 0; i<40; i++)
    {
        cm::addCard(Card(static_cast<Card::Suit>(i%4),i/4 + 1,false),cm::DECK,60+15*i,80,spriteListBuffer,cVecArr);
        cm::alterCardPriority(Card(static_cast<Card::Suit>(i%4),i/4 + 1,false),cm::DECK,static_cast<int8_t>(i)-38,spriteListBuffer,cVecArr);
    }



};

void NewMode::run()
{

    if (mRead->pressedDone && mRead->releasedDone)
    {
        mRead->pressedDone  = false;
        mRead->releasedDone = false;
        cm::shuffleCards(randGen,spriteListBuffer,cVecArr);
    }



}
