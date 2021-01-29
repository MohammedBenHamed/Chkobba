#include "MainPhase.h"

MainPhase::MainPhase(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, Mode::ModeName* mptr, MouseReading* mread,
                      bm::bStatusArr_t* bstatusarr) : spriteListBuffer(spritelistbuffer), cVecArr(cvecarr), mRead(mread),
                      bStatusArr(bstatusarr)
{
    selectedCardSprite = spriteListBuffer->end();
}

void MainPhase::updateHighlightedCards()
{
    for (Card c : sCardTableSet) cm::highlightCard(c,cm::TABLE,spriteListBuffer,cVecArr);
    if (selectedCardSprite != spriteListBuffer->end())
    {
        Card c = cm::getCardFromSprite(selectedCardSprite,spriteListBuffer,cVecArr).first;
        cm::highlightCard(c,cm::HMNHAND,spriteListBuffer,cVecArr);
    }
}

void MainPhase::updateButtons()
{
    if (selectedCardSprite != spriteListBuffer->end())
    {
        Card selectedCard = cm::getCardFromSprite(selectedCardSprite,spriteListBuffer,cVecArr).first;
        if (canEat(selectedCard) == false && sCardTableSet.empty() ) bm::activateButton(bm::PUTONTABLE,spriteListBuffer,bStatusArr);
        else bm::deactivateButton(bm::PUTONTABLE,spriteListBuffer,bStatusArr);
        if (sCardTableSet.size() > 1)
        {
            uint8_t sum = 0;
            for (Card c : sCardTableSet) sum += c.val;
            if (sum ==  selectedCard.val) bm::activateButton(bm::PLAY,spriteListBuffer,bStatusArr);
            else bm::deactivateButton(bm::PLAY,spriteListBuffer,bStatusArr);
        }
        else if (sCardTableSet.size() == 1 )
        {
            if (sCardTableSet.begin()->val == selectedCard.val) bm::activateButton(bm::PLAY,spriteListBuffer,bStatusArr);
            else bm::deactivateButton(bm::PLAY,spriteListBuffer,bStatusArr);
        }
        else bm::deactivateButton(bm::PLAY,spriteListBuffer,bStatusArr);
    }
    else
    {
        bm::deactivateButton(bm::PUTONTABLE,spriteListBuffer,bStatusArr);

    }
}

void MainPhase::run()
{
    switch(modeStage)
    {
        case PICKCARDS:
        {

            // Check if mouse has been clicked on appropriate card
            // table cannot be selected if selectedCard is at end as a card on table needs to be selected first
            //  Makes changes to selectedCardSprite and selectedTableCardVec
            // Constantly look at those two variables then update colours by using a constexpr std::array of pre-set colours
            // no new cm function needed
            if (mRead->pressedDone && mRead->releasedDone)
            {
                mRead->pressedDone  = false;
                mRead->releasedDone = false;
                for (auto it = spriteListBuffer->begin(); it != spriteListBuffer->end(); ++it)
                {
                    // Goes through all sprites, and sees if the selected sprite has been clicked on, or not
                    if (it->coordInSprite(mRead->xPressed,mRead->yPressed)
                        && it->coordInSprite(mRead->xReleased,mRead->yReleased) )
                    {
                        if (cm::spriteIsCard(it,spriteListBuffer,cVecArr)
                            && cm::getCardFromSprite(it,spriteListBuffer,cVecArr).second == cm::HMNHAND
                            && it != selectedCardSprite)
                            {
                                if (selectedCardSprite != spriteListBuffer->end())
                                {
                                    Card c = cm::getCardFromSprite(selectedCardSprite,spriteListBuffer,cVecArr).first;
                                    cm::unhighlightCard(c,cm::HMNHAND,spriteListBuffer,cVecArr);
                                }
                                selectedCardSprite = it;
                                updateHighlightedCards();
                                updateButtons();
                            }

                        else if (cm::spriteIsCard(it,spriteListBuffer,cVecArr)
                                &&cm::getCardFromSprite(it,spriteListBuffer,cVecArr).second == cm::TABLE)
                        {
                            if (selectedCardSprite != spriteListBuffer->end())
                            {// only allow table cards to be selected once card from hand has been chosen
                                Card c = cm::getCardFromSprite(it,spriteListBuffer,cVecArr).first;
                                auto cIt = std::find(sCardTableSet.begin(),sCardTableSet.end(),c);
                                if ( cIt == sCardTableSet.end() ) // add card if it is not already in set
                                sCardTableSet.insert(cm::getCardFromSprite(it,spriteListBuffer,cVecArr).first);
                                else
                                {
                                    Card c = cm::getCardFromSprite(it,spriteListBuffer,cVecArr).first;
                                    cm::unhighlightCard(c,cm::TABLE,spriteListBuffer,cVecArr);
                                    sCardTableSet.erase(cIt); // remove card from set since it has been deselected
                                }
                                updateHighlightedCards();
                                updateButtons();
                            }

                        }
                        if ( !cm::spriteIsCard(it,spriteListBuffer,cVecArr)
                            && bm::getBTypeFromSprite(it,spriteListBuffer,bStatusArr) == bm::PUTONTABLE)
                        {
                            Card selectedCard = cm::getCardFromSprite(selectedCardSprite,spriteListBuffer,cVecArr).first;;
                            cm::moveCardToHome(selectedCard,cm::HMNHAND,cm::TABLE,0,spriteListBuffer,cVecArr);
                            selectedCardSprite = spriteListBuffer->end(); // reset variable
                            updateButtons();
                            modeStage = MOVECARDS;
                        }
                        else if ( !cm::spriteIsCard(it,spriteListBuffer,cVecArr)
                            && bm::getBTypeFromSprite(it,spriteListBuffer,bStatusArr) == bm::PLAY)
                        {
                            if (cVecArr->at(cm::TABLE).size() != sCardTableSet.size())
                            {
                                Card selectedCard = cm::getCardFromSprite(selectedCardSprite,spriteListBuffer,cVecArr).first;
                                cm::flipCard(selectedCard,cm::HMNHAND,2,spriteListBuffer,cVecArr);
                                cm::unhighlightCard(selectedCard,cm::HMNHAND,spriteListBuffer,cVecArr);
                                cToFlipVec.push_back(selectedCard);
                            }

                            for (Card c: sCardTableSet)
                            {
                                cm::flipCard(c,cm::TABLE,4,spriteListBuffer,cVecArr);
                                cm::unhighlightCard(c,cm::TABLE,spriteListBuffer,cVecArr);
                                cToFlipVec.push_back(c);
                            }
                            selectedCardSprite = spriteListBuffer->end(); // reset variable
                            sCardTableSet.clear();
                            updateButtons();
                            modeStage = FLIPCARDS;
                        }
                        break; // If selected sprite is found, end for loop
                    }
                }

            }

        }
        break;
        case FLIPCARDS:
        {
            if (!cm::anyDeckUpdating(spriteListBuffer,cVecArr))
            {
                if (flipProg < cToFlipVec.size())
                {
                    if (flipProg == 0) cm::moveCardToHome(cToFlipVec.at(flipProg),cm::HMNHAND,cm::HMNPILE,0,spriteListBuffer,cVecArr);
                    else cm::moveCardToHome(cToFlipVec.at(flipProg),cm::TABLE,cm::HMNPILE,0,spriteListBuffer,cVecArr);
                    flipProg++;
                }
                else
                {
                    cToFlipVec.clear(); // reset card vector
                    flipProg = 0; // reset index
                    modeStage = MOVECARDS;
                }


            }
        }
        break;
        case MOVECARDS:
        {

            if (!cm::anyDeckUpdating(spriteListBuffer,cVecArr))
            {
                modeStage = PICKCARDS;
                mRead->pressedDone  = false;
                mRead->releasedDone = false; // reset readings
            }
        }
        break;
        case CPUPLAYS:
        {

        }
        break;
    }
}
