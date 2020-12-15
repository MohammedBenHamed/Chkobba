#include "Game.h"

void Game::updateSprites()
{
    std::vector<std::list<Sprite>::iterator> itVec; // Contains iterators pointing to Sprites to be drawn at the top
    for (auto it = spriteListBuffer.begin(); it != spriteListBuffer.end(); ++it)
    {

        if ( it->updatePending() && it->getUpdate().c == Update::MOVE && !(it)->needToWait() )
            // Prioritise sprites that are moving (which takes the waiting period into consideration)
        {
            itVec.push_back(it);
        }
        else
        it->draw(window);
    }

    for (std::list<Sprite>::iterator it : itVec)
    {
        it->draw(window); //Draw moving sprites
    }
    itVec.clear();

    if (!(text.getString() == "")) window.draw(text); // Only draw text if String is not empty

    if (clock.getElapsedTime().asMilliseconds() > 16)
    {
        clock.restart();
        std::vector<std::list<Sprite>::iterator> itVec; // Contains iterators pointing to Sprites to be deleted
        for (auto it = spriteListBuffer.begin(); it != spriteListBuffer.end(); ++it)
        {
            if ( (it)->updatePending())
            {
                if ( (it)->needToWait()  ) (it)->decWait();
                else
                {
                    const Update update = it->getUpdate();
                    switch(update.c)
                    {
                        case Update::NONE:
                        (it)->popUpdate();
                        break;
                        case Update::MOVE:
                        case Update::STRETCH:
                        {
                            float x;
                            float y;
                            if (update.c == Update::MOVE)
                            {
                                x = (it)->getCoordinates().x;
                                y = (it)->getCoordinates().y;
                            }
                            else if (update.c == Update::STRETCH)
                            {
                                x = (it)->getLengths().x;
                                y = (it)->getLengths().y;
                            }
                            float nx = (it)->getUpdate().x_new;
                            float ny = (it)->getUpdate().y_new;
                            float spd = (it)->getUpdate().spd;
                            if ( !(nx - x == 0 && ny - y ==0) ) // to prevent diving by zero
                            {
                                float ratio = static_cast<float>(spd/std::sqrt((nx-x)*(nx-x)+(ny-y)*(ny-y)));
                                float dx = (nx - x) * ratio;
                                float dy = (ny - y) * ratio;
                                if ( (nx>x && x+dx > nx) || (nx<x && x+dx<nx) || (ny>y && y+dy>ny) || (ny<y && y+dy<ny) )
                                {
                                    if (update.c == Update::MOVE) (it)->setCoordinates(nx,ny);
                                    else if (update.c == Update::STRETCH) (it)->setLengths(nx,ny);
                                }
                                else
                                {
                                    if (update.c == Update::MOVE) (it)->displace(dx,dy);
                                    else if (update.c == Update::STRETCH) (it)->stretch(dx,dy);
                                }
                            }
                            if ( x  == nx && y == ny ) (it)->popUpdate();
                        }
                        break;
                        case Update::CHANGETEX:
                        {
                            (it)->setTexture((it)->getUpdate().filename);
                            (it)->popUpdate();
                        }
                        break;
                        case Update::DELETE:
                        {
                            (it)->popUpdate();
                            itVec.push_back(it); // mark for deletion
                        }
                        break;
                        case Update::HIDE:
                        {
                            (it)->setVisibility(false);
                            (it)->popUpdate();
                        }
                        break;
                        case Update::SHOW:
                        {
                            (it)->setVisibility(true);
                            (it)->popUpdate();
                        }
                        break;

                    };
                }
            }
        }

        for (std::list<Sprite>::iterator it : itVec)
        {
            spriteListBuffer.erase(it); //Remove any sprites that have been marked for deletion
        }


    }


}
