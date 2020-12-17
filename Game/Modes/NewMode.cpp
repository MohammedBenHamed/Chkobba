#include "NewMode.h"

NewMode::NewMode(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr)
: spriteListBuffer(spritelistbuffer), cVecArr(cvecarr)
{
    for (int i = 1; i <=10; i++)
    {
        cm::addCard(Card(Card::DIAMONDS,i),cm::DECK,(i-1)*40,0,spriteListBuffer,cVecArr);
    }
    cm::moveCardToHome(Card(Card::DIAMONDS,1),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);

};

void NewMode::run()
{
    if (!done && !cm::cardUpdating(Card(Card::DIAMONDS,1),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,2),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done = true;
    }
    if (done && !done2 && !cm::cardUpdating(Card(Card::DIAMONDS,2),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,3),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done2 = true;
    }
    if (done2 && !done3 && !cm::cardUpdating(Card(Card::DIAMONDS,3),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,4),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done3 = true;
    }
    if (done3 && !done4 && !cm::cardUpdating(Card(Card::DIAMONDS,4),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,5),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done4 = true;
    }
    if (done4 && !done5 && !cm::cardUpdating(Card(Card::DIAMONDS,1),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,6),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done5 = true;
    }
    if (done5 && !done6 && !cm::cardUpdating(Card(Card::DIAMONDS,6),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,7),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done6 = true;
    }
    if (done6 && !done7 && !cm::cardUpdating(Card(Card::DIAMONDS,7),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,8),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done7 = true;
    }
    if (done7 && !done8 && !cm::cardUpdating(Card(Card::DIAMONDS,8),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,9),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done8 = true;
    }
    if (done8 && !done9 && !cm::cardUpdating(Card(Card::DIAMONDS,9),cm::TABLE,spriteListBuffer,cVecArr) )
    {
        cm::moveCardToHome(Card(Card::DIAMONDS,10),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
        done9 = true;
    }


}
