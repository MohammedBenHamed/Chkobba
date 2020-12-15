#include "Game.h"
Game::Game()
{
    window.create(sf::VideoMode(800,600), "Chkobba", sf::Style::Titlebar | sf::Style::Close);
    b_pic.loadFromFile("images/background.png");
    font.loadFromFile("images/arial.ttf");
    text = sf::Text("", font);
    background.setTexture(b_pic);
    std::srand(std::time(0));
    modename = Mode::NEWMODE;
}

void Game::modeRun()
{
    switch(modename)
    {
        case Mode::NEWMODE:
        {
            if ( dynamic_cast<NewMode*>(mode.get()) == 0) // only change mode if it is not already NEWMODE
            mode = std::unique_ptr<Mode> { std::make_unique<NewMode>(&spriteListBuffer, &cVecArr)  };
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
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.draw(background);
        updateSprites();
        modeRun();
        window.display();
    }
}
