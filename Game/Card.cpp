#include "Card.h"
Card::Card(Suit suit, uint8_t val) : suit(suit), val(val), spriteID( static_cast<uint8_t>(suit)+ 4*(val-1) ) {};

Card::Card(Suit suit, uint8_t val, bool flipped ) : suit(suit), val(val),  flipped(flipped)
{
    spriteID = static_cast<uint8_t>(suit)+ 4*(val-1);
}

Card::Card(const Card& c) : suit(c.suit), val(c.val), spriteID(c.spriteID), flipped(c.flipped) {};


std::ostream& operator<< (std::ostream &out, const Card &card) // for debugging/logging reasons
{
    if (card.val >= 2 && card.val <= 7)  out << (int)card.val; // If card is between 2 and 7, print number
    // Otherwise print the special characters
    else if (card.val == 1) out << "A";
    else if (card.val == 8) out << "Q";
    else if (card.val == 9) out << "J";
    else if (card.val == 10) out << "K";
    switch(card.suit)
    {
        case Card::HEARTS:
        out << "H"; // Alt code for Heart
        break;
        case Card::DIAMONDS:
        out << "D"; // Alt code for Diamonds
        break;
        case Card::SPADES:
        out << "S"; // Alt code for Spades
        break;
        case Card::CLUBS:
        out << "C"; // Alt code for Clubs
        break;
        default:
        break;
    };
    return out;
}

bool operator>(const Card& lhs, const Card& rhs)
{
    if (lhs.val != rhs.val) return (lhs.val > rhs.val);
    else return (lhs.suit > rhs.suit);
}
bool operator<(const Card& lhs, const Card& rhs)
{
    if (lhs.val != rhs.val) return (lhs.val < rhs.val);
    else return (lhs.suit < rhs.suit);
}
bool operator==(const Card& lhs, const Card& rhs)
{
    return std::tie(lhs.suit,lhs.val) == std::tie(rhs.suit,rhs.val);
}
bool operator!=(const Card& lhs, const Card& rhs)
{
    return std::tie(lhs.suit,lhs.val) != std::tie(rhs.suit,rhs.val);
}

