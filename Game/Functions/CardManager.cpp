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
                    float y;
                    if (from == cm::CPUHAND) y = 20;
                    else if (from == cm::HMNHAND) y = 460;
                    if (cardVecs->at(from).size() == 2)
                    {
                        if (cardVecs->at(from).at(0) == c)
                        {
                            moveCard(cardVecs->at(from).at(1),from,X_HANDC1P1,y,1.86,0,sBuffer,cardVecs);
                        }
                        else if (cardVecs->at(from).at(1) == c)
                        {
                            moveCard(cardVecs->at(from).at(0),from,X_HANDC1P1,y,1.86,0,sBuffer,cardVecs);
                        }
                    }
                    if (cardVecs->at(from).size() == 3)
                    {
                        bool firstCardMoved = false;
                        for (int i = 0; i<(int)cardVecs->at(from).size(); i++ )
                        {
                            Card card = cardVecs->at(from).at(i);
                            if ( card != c && !firstCardMoved)
                            {
                                moveCard(card,from,X_HANDC2P1,y,1.86,0,sBuffer,cardVecs);
                                firstCardMoved = true;
                            }
                            else if ( card != c && firstCardMoved) moveCard(card,from,X_HANDC2P2,y,1.86,0,sBuffer,cardVecs);
                        }
                    }
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
                    if (to == cm::CPUHAND) y = 20;
                    else if (to == cm::HMNHAND) y = 460;
                    if (cardVecs->at(to).size() == 1) moveCard(c,to,X_HANDC1P1,y,15,0,sBuffer,cardVecs);
                    else if (cardVecs->at(to).size() == 2 )
                    {
                        Card firstCard = cardVecs->at(to).at(0);
                        std::list<Sprite>::iterator firstCardIt = selectSprite(firstCard,to,sBuffer,cardVecs);
                        if (!firstCardIt->updatePending())
                        {
                            moveCard(firstCard,to,X_HANDC2P1,y,1.6,0,sBuffer,cardVecs);
                            moveCard(c,to,X_HANDC2P2,y,15,0,sBuffer,cardVecs);
                        }
                    }
                    else if (cardVecs->at(to).size() == 3 )
                    {
                        Card firstCard = cardVecs->at(to).at(0);
                        Card secondCard = cardVecs->at(to).at(1);
                        std::list<Sprite>::iterator firstCardIt = selectSprite(firstCard,to,sBuffer,cardVecs);
                        std::list<Sprite>::iterator secondCardIt = selectSprite(secondCard,to,sBuffer,cardVecs);

                        if (!firstCardIt->updatePending() && !secondCardIt->updatePending())
                        {
                            moveCard(firstCard,to,X_HANDC3P1,y,1.5,0,sBuffer,cardVecs);
                            moveCard(secondCard,to,X_HANDC3P2,y,1.868,0,sBuffer,cardVecs);
                            moveCard(c,to,X_HANDC3P3,y,15,0,sBuffer,cardVecs);
                        }
                    }
                    // else throw exception
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
