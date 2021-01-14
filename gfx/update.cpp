#include "update.h"


// TODO: Use union
Update::Update(command c, float x, float y, float spd, unsigned int wait) : c(c), x_new(x), y_new(y), spd(spd), wait(wait) {};
Update::Update(command c, std::string filename, unsigned int wait) : c(c), filename(filename), wait(wait) {};
Update::Update(command c, unsigned int wait) : c(c), wait(wait) {};
Update::Update(command c, int8_t priority) : c(c), priority_new(priority) {};
Update::Update() {};
bool operator==(const Update& lhs, const Update& rhs)
{
    bool equals = false;
    if (lhs.c == rhs.c)
    {
        switch (lhs.c)
        {
            case Update::NONE:
            case Update::DELETE:
            case Update::SHOW:
            case Update::HIDE:
            equals = lhs.wait == rhs.wait;
            break;
            case Update::MOVE:
            case Update::STRETCH:
            equals = std::tie(lhs.x_new,lhs.y_new,lhs.spd,lhs.wait) == std::tie(rhs.x_new,rhs.y_new,rhs.spd,rhs.wait);
            break;
            case Update::CHANGETEX:
            equals = std::tie(lhs.filename,lhs.wait) == std::tie(rhs.filename,rhs.wait);
            break;
            case Update::CHANGEPRIORITY:
            equals = lhs.priority_new == rhs.priority_new;
            break;
        }
    }
    return equals;
}
bool operator!=(const Update& lhs, const Update& rhs)
{
    return !(lhs == rhs);
}

