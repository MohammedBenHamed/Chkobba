#ifndef BUTTONMANAGER_H
#define BUTTONMANAGER_H
#include <list>
#include <string>
#include "../../gfx/sprite.h"
namespace bm
{
    constexpr std::array<const char*,5> buttonFilenames = {"Pick.png","Yes.png","No.png","PutOnTable.png","Play.png"};
    constexpr std::array<std::pair<float,float>,5> buttonCoords = {std::make_pair(350,260),std::make_pair(73,450),
                                            std::make_pair(587,450),std::make_pair(650,468),std::make_pair(658,481) };
    enum buttonType
    {
        PICK, YES, NO, PUTONTABLE, PLAY
    };
    typedef std::array<bool,5> bStatusArr_t;
    // The following functions draw appropriate button sprites by (de)allocating a sprite on the list and altering button status
    void activateButton(buttonType bType, std::list<Sprite>* sBuffer, bStatusArr_t* bStatusArr);
    void deactivateButton(buttonType bType, std::list<Sprite>* sBuffer, bStatusArr_t* bStatusArr);
    buttonType getBTypeFromSprite(std::list<Sprite>::iterator sIt, std::list<Sprite>* sBuffer, bStatusArr_t* bStatusArr);
}
#endif // BUTTONMANAGER_H
