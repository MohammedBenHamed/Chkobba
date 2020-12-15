#ifndef CARD_H
#define CARD_H
#include <cstdint>
#include <ostream>
#include <tuple>
struct Card
{
    enum Suit
    {
        CLUBS, DIAMONDS, HEARTS, SPADES
    };
    Suit suit;
    uint8_t val;
    uint8_t spriteID;
    bool flipped = 0;
    Card(Suit suit, uint8_t val);
    Card(Suit suit, uint8_t val, bool flipped);
    Card(const Card& c); // overload copy constructor
};
std::ostream& operator<< (std::ostream &out, const Card &card);
bool operator>(const Card& lhs, const Card& rhs);
bool operator<(const Card& lhs, const Card& rhs);
bool operator==(const Card& lhs, const Card& rhs);
bool operator!=(const Card& lhs, const Card& rhs);

#endif // CARD_H
