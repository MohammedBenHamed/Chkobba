#ifndef CMHELPERFUNCTIONS_H
#define CMHELPERFUNCTIONS_H
#include "CardManager.h"


namespace cm
{
		namespace
		{
			std::list<Sprite>::iterator selectSpriteEnd(Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
			std::vector<Card>::iterator selectCard(Card c, Deck d, cVecArr_t* cardVecs);
			std::list<Sprite>::iterator selectSprite(Card c, Deck d, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
			void transferCard(Card c, Deck from, Deck to, std::list<Sprite>* sBuffer, cVecArr_t* cardVecs);
		}
}
#endif // CMHELPERFUNCTIONS_H
