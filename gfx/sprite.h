#ifndef SPRITE_H
#define SPRITE_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <queue>
#include "update.h"
class Sprite
{
    private:
    float lenx, leny, x, y;
    sf::Sprite sprite;
    sf::Texture texture;
    std::queue<Update> updateQueue;
    bool visibility = 1;
    public:
    Sprite ();
    Sprite (float lenx, float leny, float x, float y, std::string fileName, std::queue<Update> updateQueue);
    void draw(sf::RenderWindow& window);
    void setCoordinates (float x, float y);
    void setLengths (float x, float y);
    void setTexture (sf::Texture texture);
    void setTexture (std::string fileName);
    void displace (float dx, float dy);
    void stretch (float dlenx, float dleny);
    sf::Vector2f getCoordinates() const;
    sf::Vector2f getLengths() const;
    Update getUpdate() const;
    void addUpdates(std::queue<Update> updateQueue);
    void addUpdate(Update update);
    void popUpdate();
    bool isSelected (sf::RenderWindow& window); // Returns true if user has mouse of this sprite
    bool updatePending();
    bool needToWait();
    void decWait();
    void setVisibility(bool visibility);
    int getNumOfUpdates();

};
bool operator>(const Sprite& lhs, const Sprite& rhs);
bool operator<(const Sprite& lhs, const Sprite& rhs);
std::ostream& operator<< (std::ostream &out, const Sprite &sprite);

#endif // SPRITE_H
