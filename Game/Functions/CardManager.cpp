#include "CardManager.h"
#include "CMHelperFunctions.cpp"
#include "CMMacros.h"
namespace cm
{
    void addCard(Card c, Deck d, float x, float y, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        std::list<Sprite>::iterator spriteIt = selectSpriteEnd(d,sBuffer,cardVecs);
        std::string filename;
        if (c.flipped) filename = "images/e.png";
        else filename = "images/" + std::to_string(c.spriteID) + ".png";
        Sprite sprite = Sprite(80,120,x,y,filename, std::queue<Update>{} );
        sBuffer->insert(spriteIt,sprite);
        cardVecs->at(d).push_back(c);
    }
    void removeCard(Card c, Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        std::list<Sprite>::iterator spriteIt = selectSprite(c,d,sBuffer,cardVecs);
        std::vector<Card>::iterator cardIt = selectCard(c,d,cardVecs);
        if (spriteIt != sBuffer->end())
        {
            sBuffer->erase(spriteIt);
            cardVecs->at(d).erase(cardIt);
        }
    }
    void flipCard(Card c, Deck d, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        std::list<Sprite>::iterator spriteIt = selectSprite(c,d,sBuffer,cardVecs);
        std::vector<Card>::iterator cardIt = selectCard(c,d,cardVecs);
        std::string filename;
        if (spriteIt != sBuffer->end())
        {
            if (!cardIt->flipped) filename = "images/e.png";
            else filename = "images/" + std::to_string(c.spriteID) + ".png";
            cardIt->flipped = !cardIt->flipped;
        }
        if (spriteIt != sBuffer->end()) spriteIt->addUpdates(std::queue<Update>
        ({
            Update(Update::STRETCH,20,120,6.5,4+wait), // Add the wait supplied from the arguments
            Update(Update::CHANGETEX,filename,4),
            Update(Update::STRETCH,80,120,6.5,4),
         }));

    }
    void instantFlipCard(Card c, Deck d, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        std::list<Sprite>::iterator spriteIt = selectSprite(c,d,sBuffer,cardVecs);
        std::vector<Card>::iterator cardIt = selectCard(c,d,cardVecs);
        std::string filename;
        if (spriteIt != sBuffer->end())
        {
            if (!cardIt->flipped) filename = "images/e.png";
            else filename = "images/" + std::to_string(c.spriteID) + ".png";
            cardIt->flipped = !cardIt->flipped;
        }
        if (spriteIt != sBuffer->end()) spriteIt->addUpdate(Update(Update::CHANGETEX,filename,wait));
    }
    void moveCard(Card c, Deck d, float x, float y, float spd, unsigned int wait, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        std::list<Sprite>::iterator spriteIt = selectSprite(c,d,sBuffer,cardVecs);
        if (spriteIt != sBuffer->end()) spriteIt->addUpdate(Update(Update::MOVE,x,y,spd,wait));
    }
    void moveCardToHome(Card c, Deck from, Deck to, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        std::list<Sprite>::iterator spriteIt = selectSprite(c,from,sBuffer,cardVecs);
        if (spriteIt != sBuffer->end() && ( !spriteIt->updatePending() ||  spriteIt->getUpdate().c != Update::MOVE ) )
        // Only execute if sprite is found AND sprite is not moving
        {
            switch (from) // Depending on where the card is moved from, there may be other cards in same "Deck" that must move
            {
                case cm::DECK:
                case cm::HMNPILE:
                case cm::CPUPILE:
                break; // No action needed
                case cm::HMNHAND:
                case cm::CPUHAND:
                {
                    for (int i = 0, j = 0; i<(int)cardVecs->at(from).size(); i++)
                    {
                        Card card = cardVecs->at(from).at(i);
                        if ( cardVecs->at(from).at(i) != card )
                        {
                            int x = xConstants[ xHANDStartArr[ cardVecs->at(from).size() - 2] + j ];
                            float y;
                            if (from == cm::CPUHAND) y = Y_HANDCPU;
                            else if (from == cm::HMNHAND) y = Y_HANDHMN;
                            moveCard(card,from,x,y,1.86,0,sBuffer,cardVecs);
                            j++;
                        }
                    }
                }
                break;
                case cm::TABLE:
                {

                }
                break;
            }
            transferCard(c,from,to,sBuffer,cardVecs);
            switch (to)
            {
                case cm::DECK:
                case cm::HMNPILE:
                case cm::CPUPILE:
                {
                    float x, y;
                    if (to == cm::DECK) x = 700, y = 240;
                    else if (to == cm::HMNPILE) x = 20, y = 460;
                    else if (to == cm::CPUPILE) x = 20, y = 20;
                    moveCard(c,to,x,y,15,0,sBuffer,cardVecs);
                }
                break;
                case cm::HMNHAND:
                case cm::CPUHAND:
                {
                    float y;
                    if (to == cm::CPUHAND) y = Y_HANDCPU;
                    else if (to == cm::HMNHAND) y = Y_HANDHMN;
                    for (unsigned int i = 0; i<cardVecs->at(to).size(); i++)
                    {
                        Card card = cardVecs->at(to).at(i);
                        int x = xConstants[ xHANDStartArr[ cardVecs->at(to).size() - 1] + i ];
                        float spd;
                        if (i == cardVecs->at(to).size() - 1 ) spd = 15;
                        // set speed of the last card to highest (i.e. card that has just been added)
                        else spd = 1.6;
                        moveCard(card,to,x,y,spd,0,sBuffer,cardVecs);
                    }
                }
                break;
                case cm::TABLE:
                {

                    for (unsigned int i = 0; i<cardVecs->at(to).size(); i++)
                    {
                        Card card = cardVecs->at(to).at(i);
                        int x;

                        if (cardVecs->at(to).size()<=5)
                        x = xConstants[ xTABLEStartArr[ (cardVecs->at(to).size() - 1) ] + i%5 ];
                        else if (i<5) x = xConstants[ xTABLEStartArr[ 4 ] + i%5 ];
                        else   x = xConstants[ xTABLEStartArr[ (cardVecs->at(to).size() -6) ] + i%5 ];

                        float spd;
                        if (i == cardVecs->at(to).size() - 1 ) spd = 15;
                        // set speed of the last card to highest (i.e. card that has just been added)
                        else spd = 1.6;
                        float y;

                        if (cardVecs->at(to).size()<=5) y = Y_TABLEMID;
                        else if (i<5) y = Y_TABLEUPPER;
                        else y = Y_TABLELOWER;

                        moveCard(card,to,x,y,spd,0,sBuffer,cardVecs);
                    }
                }
                break;
            }
        }
    }
    bool cardUpdating(Card c, Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        std::list<Sprite>::iterator spriteIt = selectSprite(c,d,sBuffer,cardVecs);
        return spriteIt->updatePending();
    }

}
