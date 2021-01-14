#include "ButtonManager.h"
namespace bm
{

    void activateButton(buttonType bType, std::list<Sprite>* sBuffer, bStatusArr_t* bStatusArr)
    {
        if (bStatusArr->at(bType) ==  false) // only create sprite if it's currently deactivated
        {
            bStatusArr->at(bType) = true;
            int xSize = 105, ySize = 80;
            if (bType == PUTONTABLE)
            { // Adjust coordinates correctly for PUTONTABLE
                xSize = 120;
                ySize = 105;
            }
            float x, y;
            std::tie(x,y) = bm::buttonCoords.at(bType);
            std::string filename = std::string("images/") + static_cast<std::string>(bm::buttonFilenames.at(bType));
            Sprite sprite = Sprite(xSize,ySize,x,y,filename, std::queue<Update>{} );

            std::list<Sprite>::iterator spriteIt = sBuffer->end();
            signed int sBufferOffset = 0;
            for (int i = PLAY; i>bType; i--)
            {
                if (bStatusArr->at(i) == true) sBufferOffset--;
            }
            std::advance(spriteIt,sBufferOffset);

            sBuffer->insert(spriteIt,sprite);
        }
    }
    void deactivateButton(buttonType bType, std::list<Sprite>* sBuffer, bStatusArr_t* bStatusArr)
    {
        bStatusArr->at(bType) = false;
        std::list<Sprite>::iterator spriteIt = sBuffer->end();
        signed int sBufferOffset = -1;
        for (int i = PLAY; i>bType; i--)
        {
            if (bStatusArr->at(i) == true) sBufferOffset--;
        }
        std::advance(spriteIt,sBufferOffset);
        sBuffer->erase(spriteIt);
    }
    buttonType getBTypeFromSprite(std::list<Sprite>::iterator sIt, std::list<Sprite>* sBuffer, bStatusArr_t* bStatusArr)
    {

        int spriteDistance = std::distance(sIt,sBuffer->end());

        int bFromSprite = PLAY + 1;
        while (spriteDistance >0)
        {
            if (bStatusArr->at(bFromSprite-1) == true) spriteDistance--;
            bFromSprite--;
        }
        return static_cast<buttonType>(bFromSprite);
    }
}
