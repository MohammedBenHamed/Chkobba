#include "Intro.h"

Intro::Intro(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, Mode* mptr)
: spriteListBuffer(spritelistbuffer), cVecArr(cvecarr), mPtr(mptr)
{

    //cm::moveCard(c,cm::DECK,60+15*39,80,15,16+i,spriteListBuffer,cVecArr);
    // Moving cards back (don't do with selected card)

    for (int i = 0; i<40; i++)
    {
        cm::addCard(Card(static_cast<Card::Suit>(i%4),i/4 + 1),cm::DECK,60,80,spriteListBuffer,cVecArr);
        //cm::addCard(Card(static_cast<Card::Suit>(i%4),i/4 + 1,1),cm::DECK,60+15*39,80,spriteListBuffer,cVecArr);
    }

    for (int i = 0; i<40; i++)
    {
        Card c = Card(static_cast<Card::Suit>(i%4),i/4 + 1);
        cm::moveCard(c,cm::DECK,60+15*i,80 + 9*i,17.49,0,spriteListBuffer,cVecArr);
        if (i==39) cm::alterCardPriority(c,cm::DECK,1,spriteListBuffer,cVecArr);
        cm::moveCard(c,cm::DECK,60+15*39,80 + 9*39,17.49,75,spriteListBuffer,cVecArr);

        if (i!=39)
        {

            cm::moveCard(c,cm::DECK,60+15*39,80,64.2,127-i,spriteListBuffer,cVecArr);
            cm::instantFlipCard(c,cm::DECK,0,spriteListBuffer,cVecArr);
            cm::alterCardPriority(c,cm::DECK,static_cast<int8_t>(i)-38,spriteListBuffer,cVecArr);
            cm::moveCard(c,cm::DECK,60+15*i,80,15,i,spriteListBuffer,cVecArr);

        }
        else
        {
            cm::moveCard(c,cm::DECK,60+15*39,80,25,20,spriteListBuffer,cVecArr);
            cm::flipCard(c,cm::DECK,0,spriteListBuffer,cVecArr);
        }
    }


};

void Intro::run()
{
    if (!done && !cm::deckUpdating(cm::DECK,spriteListBuffer,cVecArr))
    {
        std::cout << "Animation done, now to pick card\n";
        done = true;
    }
}
