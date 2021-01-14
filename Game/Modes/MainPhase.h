#ifndef MAINPHASE_H
#define MAINPHASE_H
#include "Mode.h"
#include "../Functions/ButtonManager.h"
#include "../Functions/CardManager.h"
#include "../MouseReading.h"
class MainPhase : public Mode
{
    private:
    enum
    {
        PICKCARD, PLAYANIMATION, CPUPLAYS
    } modeStage = PICKCARD;
    std::list<Sprite> selectedCardSprite; // current card from hand selected
    std::vector<std::list<Sprite>::iterator> selectedCardTableVec; // cards from table (if any) selected
    std::list<Sprite>* spriteListBuffer;
    Mode::ModeName* mPtr;
    cm::cVecArr_t* cVecArr;
    MouseReading* mRead;
    bm::bStatusArr_t* bStatusArr;
    public:
    MainPhase(std::list<Sprite>* spritelistbuffer, cm::cVecArr_t* cvecarr, Mode::ModeName* mptr, MouseReading* mread, bm::bStatusArr_t* bstatusarr);
    void run();

};
#endif // MAINPHASE_H
