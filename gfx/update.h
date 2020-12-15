#ifndef UPDATE_H
#define UPDATE_H
#include <cmath>
#include <string>
struct Update
{

    enum command
    {
        NONE, MOVE, STRETCH, CHANGETEX, DELETE, SHOW, HIDE
    };
    float x_new, y_new, spd;
    unsigned int wait; // Amount of frames until update is initiated
    int nx, ny; // New destination that sprite should take
    float nlenx, nleny; // New size that sprite should take
    float lenspd; // how fast to stretch sprite : unit per frame
    std::string filename = "";
    command c = NONE;
    Update(command c, float x, float y, float spd, unsigned int wait);
    Update(command c, std::string filename, unsigned int wait);
    Update(command c, unsigned int wait);

    Update(int nx,int ny,unsigned int wait, float spd);
    Update(int nx,int ny,unsigned int wait); // Instantly move sprite
    Update(float nlenx,float nleny,unsigned int wait, float lenspd);
    Update(float nlenx,float nleny,unsigned int wait); // Instantly stretch sprite
    Update (std::string filename,unsigned int wait); // Change texture
};
#endif //UPDATE_H
