#include "CardManager.h"
namespace cm
{
    // Prototype of helper functions
    namespace
    {
        std::list<Sprite>::iterator selectSpriteEnd(Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
        std::vector<Card>::iterator selectCard(Card c, Deck d, cVecArr_t* cardVecs);
        std::list<Sprite>::iterator selectSprite(Card c, Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
        void transferCard(Card c, Deck from, Deck to, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
        std::tuple<float,float,float> getMoveParams(unsigned int cSize, int pos, Deck home, float cX, float cY);
    }

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
    void alterCardPriority(Card c, Deck d, int8_t priority, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        std::list<Sprite>::iterator spriteIt = selectSprite(c,d,sBuffer,cardVecs);
        if (spriteIt != sBuffer->end())
        {
            spriteIt->addUpdate(Update(Update::CHANGEPRIORITY,priority));
        }
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
                case cm::TABLE:
                {
                    for (int i = 0, j = 0; i<(int)cardVecs->at(from).size(); i++)
                    {
                        Card card = cardVecs->at(from).at(i);
                        if ( cardVecs->at(from).at(i) != c )
                        {
                            float x, y, spd, cX, cY;
                            sf::Vector2f coordinates = selectSprite(card,to,sBuffer,cardVecs)->getCoordinates();
                            cX = coordinates.x; cY = coordinates.y;
                            std::tie(x,y,spd) = getMoveParams(cardVecs->at(from).size()-1,j,from,cX,cY);
                            moveCard(card,from,x,y,spd,0,sBuffer,cardVecs);
                            j++;
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
                { // Only move the latest card (input parameter c)
                    float x, y, spd, cX, cY;
                    sf::Vector2f coordinates = selectSprite(c,to,sBuffer,cardVecs)->getCoordinates();
                    cX = coordinates.x; cY = coordinates.y;
                    std::tie(x,y,spd) = getMoveParams(cardVecs->at(to).size(),0,to,cX,cY);
                    moveCard(c,to,x,y,spd,0,sBuffer,cardVecs);
                }
                break;
                case cm::HMNHAND:
                case cm::CPUHAND:
                case cm::TABLE:
                { // Move all cards in the deck
                    for (unsigned int i = 0; i<cardVecs->at(to).size(); i++)
                    {
                        float x, y, spd, cX, cY;
                        Card card = cardVecs->at(to).at(i);
                        sf::Vector2f coordinates = selectSprite(card,to,sBuffer,cardVecs)->getCoordinates();
                        cX = coordinates.x; cY = coordinates.y;
                        std::tie(x,y,spd) = getMoveParams(cardVecs->at(to).size(),i,to,cX,cY);
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

    bool deckUpdating(Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
    {
        bool updating = false;
        for (auto it = cardVecs->at(d).begin() ; it!= cardVecs->at(d).end(); ++it)
        {
            if (selectSprite(*it,d,sBuffer,cardVecs)->updatePending() == true) updating = true;
        }
        return updating;
    }

    // Defining helper functions
    namespace
    {
        std::list<Sprite>::iterator selectSpriteEnd(Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
        {
            auto spriteIt = sBuffer->begin();
            int distance = 0;
            for (int i = DECK; i<=d; i++)
            {
                distance += cardVecs->at(i).size(); // Add up sizes until d, first size (DECK) will be ignored
            }
            std::advance(spriteIt,distance);
            return spriteIt;
        }
        std::vector<Card>::iterator selectCard(Card c, Deck d, cVecArr_t* cardVecs)
        {
            return std::find(cardVecs->at(d).begin(),cardVecs->at(d).end(),c);
        }
        std::list<Sprite>::iterator selectSprite(Card c, Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
        {
            auto spriteIt = sBuffer->begin();
            auto it = std::find(cardVecs->at(d).begin(),cardVecs->at(d).end(),c);
            int distance = std::distance(cardVecs->at(d).begin(),it); // position of card in particular deck vector
            for (int i = DECK; i<d; i++)
            {
                distance += cardVecs->at(i).size(); // Add up sizes until (d-1), first size (DECK) will be ignored
            }
            std::advance(spriteIt,distance); // advance to relevant position
            return spriteIt;
        }
        void transferCard(Card c, Deck from, Deck to, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs)
        {
            std::list<Sprite>::iterator spriteIt = selectSprite(c,from,sBuffer,cardVecs);
            float x = spriteIt->getCoordinates().x; float y = spriteIt->getCoordinates().y;
            // x and y temporarily store coordinates for the transfer
            removeCard(c,from,sBuffer,cardVecs);
            addCard(c,to,x,y,sBuffer,cardVecs);
        }

        std::tuple<float,float,float> getMoveParams(unsigned int cSize, int pos, Deck home, float cX, float cY)
        {
            float x, y, spd;
            switch (home)
            {
                case cm::DECK:
                x = 700, y = 240;
                break;
                case cm::HMNPILE:
                x = 20, y = 460;
                break;
                case cm::CPUPILE:
                x = 20, y = 20;
                break;
                case cm::HMNHAND:
                case cm::CPUHAND:
                {
                    if (home == cm::CPUHAND) y = Y_HANDCPU;
                    else y = Y_HANDHMN;
                    if (cSize == 1) x = xHandOddConsts[1];
                    else if (cSize == 2) x = xHandEvenConsts[pos];
                    else if (cSize == 3) x = xHandOddConsts[pos];
                }
                break;
                case cm::TABLE:
                {
                    if (cSize<=5) y = Y_TABLEMID;
                    else if (pos<5) y = Y_TABLEUPPER;
                    else y = Y_TABLELOWER;
                    if (cSize>5 && pos>=5)  //  Use 1-5 sizes for pos values more than 5
                    {
                        cSize -= 5;
                        pos   -= 5;
                    }
                    else if (cSize>5 && pos <5) cSize = 5; // Use cSize 5 for first 5 cards
                    if (cSize%2 == 0 ) // even Size
                    {
                        int start = (4 - cSize)/2;
                        x = xTableEvenConsts[start + pos];
                    }
                    else
                    {
                        int start = (5 - cSize)/2;
                        x = xTableOddConsts[start + pos];
                    }
                };
                break;
            }
            float distance = std::sqrt( (x-cX)*(x-cX) + (y-cY)*(y-cY) ); // calculate distance using Pythagoras' theorem
            spd = distance/30; // Speed is calculated so movement takes half a second i.e. 30 frames
            return std::make_tuple(x,y,spd);
        }


    }



}
