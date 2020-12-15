#include "sprite.h"

Sprite::Sprite(float lenx, float leny, float x, float y, std::string fileName, std::queue<Update> updateQueue)
: lenx(lenx), leny(leny), x(x), y(y), updateQueue(updateQueue)
{
    texture.loadFromFile(fileName);
    texture.setSmooth(1);
    sprite.setOrigin(0,0);
}

Sprite::Sprite() : lenx(0),leny(0) {};

void Sprite::draw(sf::RenderWindow& window)
{
    int tex_x = texture.getSize().x;
    int tex_y = texture.getSize().y;
    sprite.setScale(lenx/tex_x,leny/tex_y);
    sprite.setTexture(texture);
    sprite.setPosition(x+(tex_x-lenx)/2,y+(tex_y-leny)/2);
    if (visibility) window.draw(sprite);
}
void Sprite::setCoordinates (float x, float y)
{
    this->x = x;
    this->y = y;
}
void Sprite::setLengths (float x, float y)
{
    lenx = x;
    leny = y;
}
void Sprite::setTexture (sf::Texture texture) {this->texture = texture;}
void Sprite::setTexture (std::string fileName) {texture.loadFromFile(fileName);}
void Sprite::displace(float dx, float dy) {x+= dx; y+= dy;}

bool Sprite::isSelected(sf::RenderWindow& window)
{
    if (window.hasFocus() == 0 || !visibility ) return 0;
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    if (mPos.x > x && mPos.x < (x + lenx -1) && mPos.y > y && mPos.y < (y + leny -1))
    {
        return 1;
    }
    else return 0;
}
void Sprite::stretch(float dlenx, float dleny) {lenx+=dlenx; leny+=dleny;}
sf::Vector2f Sprite::getCoordinates() const {return sf::Vector2f(x,y);}
sf::Vector2f Sprite::getLengths() const {return sf::Vector2f(lenx,leny);}
Update Sprite::getUpdate() const {return updateQueue.front();}

void Sprite::addUpdates(std::queue<Update> updateQueue)
{
    // add updates from input queue to this queue
    while (!updateQueue.empty())
    {
        this->updateQueue.push(updateQueue.front());
        updateQueue.pop();
    }
}
void Sprite::addUpdate(Update update)
{
    this->updateQueue.push(update);
}


void Sprite::popUpdate() {updateQueue.pop();}
bool Sprite::updatePending()
{
    return updateQueue.size() != 0;
}
bool Sprite::needToWait() {return updateQueue.front().wait != 0;}
void Sprite::decWait() {updateQueue.front().wait--;}
void Sprite::setVisibility(bool visibility) {this->visibility = visibility;}

int Sprite::getNumOfUpdates(){return updateQueue.size();}




bool operator>(const Sprite& lhs, const Sprite& rhs)
{
    if (lhs.getCoordinates().y!= rhs.getCoordinates().y)
    {
        return lhs.getCoordinates().y > rhs.getCoordinates().y;
    }
    else if (lhs.getCoordinates().x != rhs.getCoordinates().x)
    {
        return lhs.getCoordinates().x > rhs.getCoordinates().x;
    }
    return 1;
}
bool operator<(const Sprite& lhs, const Sprite& rhs)
{
    if (lhs.getCoordinates().y != rhs.getCoordinates().y)
    {
        return lhs.getCoordinates().y < rhs.getCoordinates().y;
    }
    else if (lhs.getCoordinates().x != rhs.getCoordinates().x)
    {
        return lhs.getCoordinates().x < rhs.getCoordinates().x;
    }
    return 1;
}



std::ostream& operator<< (std::ostream &out, const Sprite &sprite) // for debugging/logging reasons
{
    out << sprite.getCoordinates().x << " " << sprite.getCoordinates().y;
    return out;
}
