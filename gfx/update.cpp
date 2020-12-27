#include "update.h"


// TODO: Check for valid commands
Update::Update(command c, float x, float y, float spd, unsigned int wait) : c(c), x_new(x), y_new(y), spd(spd), wait(wait) {};
Update::Update(command c, std::string filename, unsigned int wait) : c(c), filename(filename), wait(wait) {};
Update::Update(command c, unsigned int wait) : c(c), wait(wait) {};
Update::Update(command c, int8_t priority) : c(c), priority_new(priority) {};


