#include "CMHelperFunctions.h"
namespace cm
{
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
		}
}
