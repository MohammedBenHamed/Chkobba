#ifndef MAINPHASE_H
#define MAINPHASE_H
#include "Mode.h"
#include <set>
#include "../Functions/ButtonManager.h"
#include "../Functions/CardManager.h"
#include "../MouseReading.h"
class MainPhase : public Mode
{
    private:
    enum
    {
        PICKCARDS, FLIPCARDS, MOVECARDS, CPUPLAYS
    } modeStage = PICKCARDS;
    std::list<Sprite>::iterator selectedCardSprite;
     // current card from hand selected, end() means no card selected
    std::set<Card> sCardTableSet; // cards from table (if any) selected
    std::list<Sprite>* spriteListBuffer;
    Mode::ModeName* mPtr;
    cm::cVecArr_t* cVecArr;
    MouseReading* mRead;
    bm::bStatusArr_t* bStatusArr;
    std::vector<Card> cToFlipVec; // used in FLIPCARDS to govern moveCardToHome order
    unsigned int flipProg = 0; // used in FLIPCARDS as the index to access cToFlipVec

    public:
    MainPhase(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, Mode::ModeName* mptr, MouseReading* mread, bm::bStatusArr_t* bstatusarr);
    void run();
    bool canEat(Card c);
    void updateHighlightedCards();
    void updateButtons();

};
#endif // MAINPHASE_H
