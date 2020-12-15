#include "NewMode.h"

NewMode::NewMode(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr)
: spriteListBuffer(spritelistbuffer), cVecArr(cvecarr)
{
    for (int i = 1; i <=4; i++)
    {
        cm::addCard(Card(Card::DIAMONDS,i),cm::DECK,(i-1)*40,0,spriteListBuffer,cVecArr);
    }
    cm::moveCardToHome(Card(Card::DIAMONDS,1),cm::DECK,cm::HMNHAND,spriteListBuffer,cVecArr);
};

void NewMode::run()
{
    if (!done && !cm::cardUpdating(Card(Card::DIAMONDS,1),cm::HMNHAND,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,2),cm::DECK,cm::HMNHAND,spriteListBuffer,cVecArr);
        done = true;
    }
    if (done && !done2 && !cm::cardUpdating(Card(Card::DIAMONDS,2),cm::HMNHAND,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,3),cm::DECK,cm::HMNHAND,spriteListBuffer,cVecArr);
        done2 = true;
    }
    if (done && done2 && !done3 && !cm::cardUpdating(Card(Card::DIAMONDS,3),cm::HMNHAND,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,3),cm::HMNHAND,cm::DECK,spriteListBuffer,cVecArr);
        done3 = true;
    }
}




