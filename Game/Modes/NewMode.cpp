#include "NewMode.h"

NewMode::NewMode(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr)
: spriteListBuffer(spritelistbuffer), cVecArr(cvecarr)
{
    for (int i = 1; i <=10; i++)
    {
        cm::addCard(Card(Card::DIAMONDS,i),cm::DECK,(i-1)*40,0,spriteListBuffer,cVecArr);
    }
};

void NewMode::run()
{
    if (!cm::deckUpdating(cm::DECK,spriteListBuffer,cVecArr) && !cm::deckUpdating(cm::TABLE,spriteListBuffer,cVecArr)  )
    {
        if (STAGE<=10)
        {
            cm::moveCardToHome(Card(Card::DIAMONDS,STAGE),cm::DECK,cm::TABLE,spriteListBuffer,cVecArr);
            STAGE++;
        }
    }
}
