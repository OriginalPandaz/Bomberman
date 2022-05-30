#ifndef BOMBERMAN_H
#define BOMBERMAN_H
#include "../Game/Game.h"
#include "../Bomberman/background.h"

class Bomberman : public Game
{

public:
    Bomberman();
    void start(sf::RenderWindow &window);
    void addEvents(sf::RenderWindow &window);
    void draw(sf::RenderTarget &window, sf::RenderStates states) const;
    void exit();

public:
    int rightCounter = 0, upCounter = 0, leftCounter = 0;

private:
    Background *backgrounds = new Background;
};

#endif // BOMBERMAN_H
