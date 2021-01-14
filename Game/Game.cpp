#include "Game.h"
Game::Game()
{
    window.create(sf::VideoMode(800,600), "Chkobba", sf::Style::Titlebar | sf::Style::Close);
    b_pic.loadFromFile("images/background.png");
    font.loadFromFile("images/arial.ttf");
    text = sf::Text("", font);
    background.setTexture(b_pic);
    std::srand(std::time(0));
    modename = Mode::INTRO;
}

void Game::modeRun()
{
    switch(modename)
    {
        case Mode::NEWMODE:
        {
            if ( dynamic_cast<NewMode*>(mode.get()) == 0) // only change mode if it is not already NEWMODE
            {
                mode = std::unique_ptr<Mode> { std::make_unique<NewMode>(&spriteListBuffer, &cVecArr, &mReading, &bStatusArr,
                                                                         &randGen)  };
            }
        }
        break;
        case Mode::INTRO:
        {
            if ( dynamic_cast<Intro*>(mode.get()) == 0) // only change mode if it is not already INTRO
            {
                mode = std::unique_ptr<Mode> { std::make_unique<Intro>(&spriteListBuffer, &cVecArr, &modename ,&text,
                                                                    &mReading, &bStatusArr, &randGen)  };
            }
        }
        break;
        case Mode::MAINPHASE:
        {
            if ( dynamic_cast<MainPhase*>(mode.get()) == 0) // only change mode if it is not already MAINPHASE
            {
                mode = std::unique_ptr<Mode> { std::make_unique<MainPhase>(&spriteListBuffer, &cVecArr, &modename,
                                                                        &mReading, &bStatusArr)  };
            }
        }
        break;
        default:
        // Throw exception
        break;
    }
    mode->run();
}

void Game::run()
{
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                   mReading.xPressed = event.mouseButton.x;
                   mReading.yPressed = event.mouseButton.y;
                   mReading.pressedDone = true;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    mReading.xReleased = event.mouseButton.x;
                    mReading.yReleased = event.mouseButton.y;
                    mReading.releasedDone = true;
                }
            }
        }
        window.clear();
        window.draw(background);
        updateSprites();
        modeRun();
        window.display();
    }
}


bool Game::compFunc::operator()(const std::list<Sprite>::iterator &lhs, const std::list<Sprite>::iterator &rhs) const
{
    if (lhs->getPriority() != rhs->getPriority()) return lhs->getPriority() < rhs->getPriority();
    // Check if priority values differ
    else if (lhs->updatePending() != rhs->updatePending())
    return lhs->updatePending() < rhs->updatePending();
    else return std::distance(lhs,rhs)<0;
    // Otherwise, draw cards that aren't updating first
}
