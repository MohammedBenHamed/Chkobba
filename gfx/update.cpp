#include "update.h"

Update::Update(int nx,int ny,unsigned int wait, float spd) : nx(nx), ny(ny), wait(wait), spd(spd),lenspd(0) {};
Update::Update(int nx,int ny,unsigned int wait) : nx(nx), ny(ny), wait(wait), spd(1000),lenspd(0) {};
// spd is set to a high number to cause sprite to move instantaneously
Update::Update(float nlenx,float nleny,unsigned int wait, float lenspd) : nlenx(nlenx), nleny(nleny), wait(wait), spd(0), lenspd(lenspd) {};
Update::Update(float nlenx,float nleny,unsigned int wait) : nlenx(nlenx), nleny(nleny), wait(wait), spd(0), lenspd(1000) {};
// lenspd is set to a high number to cause sprite to be stretched instantaneously
Update::Update(std::string filename,unsigned int wait) : wait(wait), spd(0), lenspd(0), filename(filename) {};


// TODO: Check for valid commands
Update::Update(command c, float x, float y, float spd, unsigned int wait) : c(c), x_new(x), y_new(y), spd(spd), wait(wait) {};
Update::Update(command c, std::string filename, unsigned int wait) : c(c), filename(filename), wait(wait) {};
Update::Update(command c, unsigned int wait) : c(c), wait(wait) {};


