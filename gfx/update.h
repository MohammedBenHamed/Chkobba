#ifndef UPDATE_H
#define UPDATE_H
#include <cmath>
#include <string>
#include <tuple>
struct Update
{

    enum command
    {
        NONE, MOVE, STRETCH, CHANGETEX, DELETE, SHOW, HIDE, CHANGEPRIORITY
    };
    command c = NONE;
    float x_new, y_new, spd = 0;
    int8_t priority_new;
    std::string filename = "";
    unsigned int wait = 0; // Amount of frames until update is initiated
    Update(command c, float x, float y, float spd, unsigned int wait);
    Update(command c, std::string filename, unsigned int wait);
    Update(command c, unsigned int wait);
    Update(command c, int8_t priority);
    Update();

};
bool operator==(const Update& lhs, const Update& rhs);
bool operator!=(const Update& lhs, const Update& rhs);
#endif //UPDATE_H
