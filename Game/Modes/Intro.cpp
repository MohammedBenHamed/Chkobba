#include "Intro.h"

Intro::Intro(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, Mode::ModeName* mptr, sf::Text* tptr, MouseReading* mread, bm::bStatusArr_t* bstatusarr, std::mt19937* randgen)
: spriteListBuffer(spritelistbuffer), cVecArr(cvecarr), mPtr(mptr), tPtr(tptr), mRead(mread), bStatusArr(bstatusarr), randGen(randgen)
{

    // -- NORMAL
    /*
    for (int i = 0; i<40; i++)
    {
        cm::addCard(Card(static_cast<Card::Suit>(i%4),i/4 + 1),cm::DECK,60,80,spriteListBuffer,cVecArr);
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
    */
    // - INSTANT
    for (int i = 0; i<40; i++)
    {
        cm::addCard(Card(static_cast<Card::Suit>(i%4),i/4 + 1,true),cm::DECK,60+15*i,80,spriteListBuffer,cVecArr);
        cm::alterCardPriority(Card(static_cast<Card::Suit>(i%4),i/4 + 1,true),cm::DECK,static_cast<int8_t>(i)-38,spriteListBuffer,cVecArr);
    }
};

void Intro::run()
{
    switch(modeStage)
    {
        case INTRO_ANIM:
        {
            if (!cm::deckUpdating(cm::DECK,spriteListBuffer,cVecArr))
            {
                cm::shuffleCards(randGen,spriteListBuffer,cVecArr);
                tPtr->setString("Please select a card.");
                tPtr->setCharacterSize(30);
                tPtr->setFillColor(sf::Color(0,0,0));
                tPtr->setPosition(250,400);
                modeStage = CHOOSECARD;
                // Start asking for input
                mRead->pressedDone  = false;
                mRead->releasedDone = false;
                // reset mouse reading to false, to be read later
            }
        }
        break;
        case CHOOSECARD:
        {
            for (auto it = spriteListBuffer->begin(); it != spriteListBuffer->end() ; ++it)
            {
                if (!cm::spriteIsCard(it,spriteListBuffer,cVecArr) ) break; // do not check sprite if it is not a card
                float yPos, xPos = it->getCoordinates().x;
                if (it != selectedCardSprite) yPos = 80;
                else if (it == selectedCardSprite) yPos = 40;
                Update currentUpdate;
                if (it->updatePending())
                {
                    currentUpdate = it->getUpdate();
                    if (currentUpdate.y_new != yPos ) it->clearUpdates();
                }
                if (it->getCoordinates().y != yPos && ( !it->updatePending() || currentUpdate.y_new != yPos ) )
                    cm::moveCard(it,xPos,yPos,4,2,spriteListBuffer);
            }
            if (mRead->pressedDone && mRead->releasedDone)
            {
                mRead->pressedDone  = false;
                mRead->releasedDone = false;
                auto selectedSpriteTemp = spriteListBuffer->end(); // Contains last selected sprite, end() means there are no sprites
                for (auto it = spriteListBuffer->begin(); it != spriteListBuffer->end(); ++it)
                {
                    // Goes through all sprites, and sees if the selected sprite has been clicked on, or not
                    if (it->coordInSprite(mRead->xPressed,mRead->yPressed) && it->coordInSprite(mRead->xReleased,mRead->yReleased))
                    selectedSpriteTemp = it;
                }
                if (selectedSpriteTemp != spriteListBuffer->end() && cm::spriteIsCard(selectedSpriteTemp,spriteListBuffer,cVecArr) )
                {
                    selectedCardSprite = selectedSpriteTemp;
                    tPtr->setString("");
                    bm::activateButton(bm::PICK,spriteListBuffer,bStatusArr);
                }
                else if ( selectedSpriteTemp != spriteListBuffer->end() && !cm::spriteIsCard(selectedSpriteTemp,spriteListBuffer,cVecArr) )
                {
                    bm::deactivateButton(bm::PICK,spriteListBuffer,bStatusArr);
                    modeStage = MOVECARDSBACK;
                }
            }
        }
        break;
        case MOVECARDSBACK:
        {
            bool advance = true;
            for (auto it = spriteListBuffer->begin(); it!=spriteListBuffer->end(); ++it)
            {
                if (it != selectedCardSprite && cm::spriteIsCard(it,spriteListBuffer,cVecArr) && it->getCoordinates().y != 80 ) advance = false;
            }
            if (advance)
            {
                int cardPos = 0;
                float newX = 60+15*39;
                if (selectedCardSprite->getCoordinates().x == 60+15*39) newX = 60+15*38;
                for (auto it = spriteListBuffer->begin(); it != spriteListBuffer->end(); ++it)
                {
                    if (it != selectedCardSprite) cm::moveCard(it,newX,80,15,2+cardPos,spriteListBuffer);
                    cardPos++;
                }
                float x = selectedCardSprite->getCoordinates().x, y = selectedCardSprite->getCoordinates().y, cX = 360, cY = 60;
                float distance = std::sqrt( (x-cX)*(x-cX) + (y-cY)*(y-cY) ); // calculate distance using Pythagoras' theorem
                float spd = distance/25; // Speed is calculated so movement takes 25 frames
                cm::moveCard(selectedCardSprite,cX,cY,spd,52,spriteListBuffer);
                Card c = cm::getCardFromSprite(selectedCardSprite,spriteListBuffer,cVecArr).first;
                cm::Deck d = cm::getCardFromSprite(selectedCardSprite,spriteListBuffer,cVecArr).second;
                cm::flipCard(c,d,2,spriteListBuffer,cVecArr);
                modeStage = KEEPORNOT;
            }
        }
        break;
        case KEEPORNOT:
        {
            if (!cm::deckUpdating(cm::DECK,spriteListBuffer,cVecArr))
            {
                tPtr->setString("Would you like to keep this card?");
                tPtr->setPosition(180,350); // readjust coordinates
                bm::activateButton(bm::YES,spriteListBuffer,bStatusArr);
                bm::activateButton(bm::NO,spriteListBuffer,bStatusArr);
                modeStage = CHOOSEOPTION;
            }
        }
        break;
        case CHOOSEOPTION:
        {
            if (mRead->pressedDone && mRead->releasedDone)
            {
                mRead->pressedDone  = false;
                mRead->releasedDone = false;
                auto selectedSpriteTemp = spriteListBuffer->end(); // Contains last selected sprite, end() means there are no sprites
                for (auto it = spriteListBuffer->begin(); it != spriteListBuffer->end(); ++it)
                {
                    // Goes through all sprites, and sees if the selected sprite has been clicked on, or not
                    if (it->coordInSprite(mRead->xPressed,mRead->yPressed) && it->coordInSprite(mRead->xReleased,mRead->yReleased))
                    selectedSpriteTemp = it;
                }
                if (selectedSpriteTemp != spriteListBuffer->end() && !cm::spriteIsCard(selectedSpriteTemp,spriteListBuffer,cVecArr) )
                {
                    tPtr->setString("");
                    Card selectedCard = cm::getCardFromSprite(selectedCardSprite,spriteListBuffer,cVecArr).first;
                    buttonClicked = bm::getBTypeFromSprite(selectedSpriteTemp,spriteListBuffer,bStatusArr);
                    bm::deactivateButton(bm::YES,spriteListBuffer,bStatusArr);
                    bm::deactivateButton(bm::NO,spriteListBuffer,bStatusArr);

                    if (buttonClicked == bm::YES)
                    {
                        cm::moveCardToHome(selectedCard,cm::DECK,cm::HMNHAND,1,spriteListBuffer,cVecArr);
                    }
                    else if (buttonClicked == bm::NO)
                    {
                        cm::moveCardToHome(selectedCard,cm::DECK,cm::TABLE,1,spriteListBuffer,cVecArr);
                    }
                    modeStage = DEALCARDS;
                }
            }
        }
        break;
        case DEALCARDS:
        {
            for (int i = 0; i<3; i++)
            {
                if (!cm::deckUpdating(decksToDeal[i],spriteListBuffer,cVecArr))
                {
                    unsigned int compare = 3;
                    if (decksToDeal[i] == cm::TABLE) compare = 4;
                    Card c = cVecArr->at(cm::DECK).back(); // Move card from DECK vector
                    if (cVecArr->at(decksToDeal[i]).size() < compare)
                    {
                        cm::moveCardToHome(c,cm::DECK,decksToDeal[i],1,spriteListBuffer,cVecArr);
                        if (decksToDeal[i] != cm::CPUHAND  ) cm::flipCard(c,decksToDeal[i],0,spriteListBuffer,cVecArr);
                    }
                }
            }
            if (!cm::deckUpdating(cm::HMNHAND,spriteListBuffer,cVecArr) && !cm::deckUpdating(cm::CPUHAND,spriteListBuffer,cVecArr)
                && !cm::deckUpdating(cm::TABLE,spriteListBuffer,cVecArr))
            {
                for (auto it = cVecArr->at(cm::DECK).begin(); it != cVecArr->at(cm::DECK).end(); ++it)
                {
                    cm::moveCardToHome(*it,cm::DECK,cm::DECK,0,spriteListBuffer,cVecArr);
                }
                modeStage = DRAWBUTTON;
            }
        }
        break;
        case DRAWBUTTON:
        {
            if (!cm::deckUpdating(cm::DECK,spriteListBuffer,cVecArr)) *mPtr = Mode::MAINPHASE;
        }
        break;
    }



}
