#include "MainPhase.h"

bool MainPhase::canEat(Card c)
{
    std::set<uint8_t> valSet;

    for (auto it = cVecArr->at(cm::TABLE).begin(); it != cVecArr->at(cm::TABLE).end(); ++it)
    {
        valSet.insert(it->val);
    }
    auto it = std::find(valSet.begin(),valSet.end(),c.val);
    if (it != valSet.end()) return true; // set true if exact val exists

    // Otherwise, check if any two vals in valSet can add up to c's val

    for (auto it = valSet.begin(); it != valSet.end(); ) // Erase all numbers larger or equal to c's val
    {
        if(*it >=c.val ) it = valSet.erase(it);
        else ++it;
    }

    for (auto it = valSet.begin(); it != valSet.end(); ++it)
    {
        for (auto nextIt = std::next(it); nextIt != valSet.end(); ++nextIt)
        {
            if ( *it + *nextIt == c.val) return true;
        }
    }

    return false;

}
