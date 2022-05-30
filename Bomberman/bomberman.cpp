#include "../Bomberman/bomberman.h"
#include <iostream>

using namespace std;
Bomberman::Bomberman()
{
    image_path = "Bomberman/images/bomberman_thumbnail.jpg";
    title = "Bomberman";
    info_path = "Bomberman/info.txt";
    load_game();
}

void Bomberman::start(sf::RenderWindow &window)
{
    //Sets all the texts and sprites needed to their position for the game
    backgrounds->windowsp.setPosition(window.getSize().x/2 - backgrounds->windowsp.getGlobalBounds().width/2,window.getSize().y/2 - backgrounds->windowsp.getGlobalBounds().height/2);
    backgrounds->clocktext.setPosition(window.getSize().x/2 - backgrounds->clocktext.getGlobalBounds().width/2 - 85,window.getSize().y - backgrounds->clocktext.getGlobalBounds().height/2 - 968);
    backgrounds->lives.setPosition(window.getSize().x/2 - backgrounds->lives.getGlobalBounds().width/2+123,window.getSize().y/2 - backgrounds->lives.getGlobalBounds().height/2-427);
    backgrounds->score.setPosition(window.getSize().x/2 - backgrounds->score.getGlobalBounds().width/2 - 210, window.getSize().y/2 - backgrounds->score.getGlobalBounds().height/2 - 427);
    backgrounds->hiScores.setPosition(window.getSize().x/2 - backgrounds->hiScores.getGlobalBounds().width/2 + 540, window.getSize().y/2 - backgrounds->hiScores.getGlobalBounds().height/2 - 427);
    backgrounds->victory.setPosition(window.getSize().x/2 - backgrounds->victory.getGlobalBounds().width/2, window.getSize().y/2 - backgrounds->victory.getGlobalBounds().height/2 - 150);
    backgrounds->cont.setPosition(window.getSize().x/2 - backgrounds->cont.getGlobalBounds().width/2, window.getSize().y/2 - backgrounds->cont.getGlobalBounds().height/2 + 100);
    float i = window.getSize().x/2 - backgrounds->bordersp[0].getGlobalBounds().width/2;
    float j = window.getSize().y/2 - backgrounds->bordersp[0].getGlobalBounds().height/2;
    backgrounds->bordersp[0].setPosition(i-2,j-305);
    backgrounds->bordersp[1].setPosition(i-2,j+420);
    backgrounds->bordersp[2].setPosition(i+975,j-290);
    backgrounds->bordersp[3].setPosition(i-8,j-290);
    backgrounds->gameoversp.setPosition(window.getSize().x/2 - backgrounds->gameoversp.getGlobalBounds().width/2, window.getSize().y/2 - backgrounds->gameoversp.getGlobalBounds().height/2);
    backgrounds->setLives();
    backgrounds->setSounds();
    backgrounds->setDefaultEnemyPos();
}

void Bomberman::addEvents(sf::RenderWindow &window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //If character moves left then it will move and trigger that the key was left and the others do their part
    {
        leftCounter++;
        if(leftCounter <= 30)
            if(!backgrounds->bombermantex.loadFromFile("Bomberman/images/bm_left_1.png"))
            {
                cout << "The image with bomberman staring right was not found!\n";
            }
        if(leftCounter > 30)
            if(!backgrounds->bombermantex.loadFromFile("Bomberman/images/bm_left_2.png"))
            {
                cout << "The image with bomberman staring right was not found!\n";
            }
        if(leftCounter == 60)
            leftCounter = 0;
        backgrounds->bombermansp.setTexture(backgrounds->bombermantex);
        backgrounds->bombermansp.move(-1.5,0);
        backgrounds->left = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        rightCounter++;
        if(rightCounter <= 30)
            if(!backgrounds->bombermantex.loadFromFile("Bomberman/images/bm_right_1.png"))
            {
                cout << "The image with bomberman staring right was not found!\n";
            }
        if(rightCounter >30)
            if(!backgrounds->bombermantex.loadFromFile("Bomberman/images/bm_right_2.png"))
            {
                cout << "The image with bomberman staring right was not found!\n";
            }
        if(rightCounter == 60)
            rightCounter = 0;
        backgrounds->bombermansp.setTexture(backgrounds->bombermantex);
        backgrounds->bombermansp.move(1.5,0);
        backgrounds->right = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        upCounter++;
        if(upCounter <= 30)
            if(!backgrounds->bombermantex.loadFromFile("Bomberman/images/bm_up_1.png"))
            {
                cout << "The image with bomberman staring right was not found!\n";
            }

        if(upCounter > 30)
            if(!backgrounds->bombermantex.loadFromFile("Bomberman/images/bm_up_2.png"))
            {
                cout << "The image with bomberman staring right was not found!\n";
            }
        if(upCounter > 60)
            upCounter = 0;
        backgrounds->bombermansp.setTexture(backgrounds->bombermantex);
        backgrounds->bombermansp.move(0,-1.5);
        backgrounds->up = true;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if(!backgrounds->bombermantex.loadFromFile("Bomberman/images/bm_down_2.png"))
        {
            cout << "The image with bomberman staring right was not found!\n";
        }
        backgrounds->bombermansp.setTexture(backgrounds->bombermantex);
        backgrounds->bombermansp.move(0,1.5);
        backgrounds->down = true;
    }
    if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)
         || sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
    {
        backgrounds->setDefaultAnimation();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && backgrounds->bombPlaced == false) //Sets the bomb down under bomberman after pressing Space
    {
        backgrounds->bombcounter = 0;
        backgrounds->bombindex = 0;
        backgrounds->explosioncounter = 0;
        backgrounds->explosionindex = 0;
        backgrounds->bombPlaced = true;
        backgrounds->onBomb = true;
        backgrounds->explosionTime = false;
        if(!backgrounds->bombtex.loadFromFile("Bomberman/images/bomb/bomb.png"))
        {
            cout << "Bomb picture was not found!\n";
        }
        backgrounds->bombsp.setTexture(backgrounds->bombtex);
        backgrounds->bombsp.setPosition(backgrounds->bombermansp.getPosition().x, backgrounds->bombermansp.getPosition().y);
    }
    if(backgrounds->numLives == 0 || backgrounds->win == true) //Checks if the player is out of lives, if so they can restart the game by pressing enter
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //After pressing enter it resets the lives count and timer and background
        {
            backgrounds->timer = backgrounds->clock.restart();
            backgrounds->numLives = 3;
            backgrounds->setLives();
            backgrounds->restartGame();
        }
}

void Bomberman::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
    window.clear(sf::Color::Black);
    backgrounds->CheckBorderCollision();
    backgrounds->CheckEnemyCollision();
    backgrounds->CheckBlockerCollision();
    backgrounds->CheckBlocksCollision();
    backgrounds->CheckBombCollision();
    backgrounds->CheckExplosionCollision();
    backgrounds->CheckGateCollision();
    backgrounds->setScores();
    backgrounds->setTimer();
    backgrounds->drawBlocks(window);
    for(int i = 0; i < 4; i++)
        window.draw(backgrounds->bordersp[i]);
    window.draw(backgrounds->windowsp,states);
    window.draw(backgrounds->clocktext,states);
    window.draw(backgrounds->lives,states);
    window.draw(backgrounds->score,states);
    window.draw(backgrounds->hiScores,states);
    if(backgrounds->bombPlaced == true) //If the user places a bomb then the animation will play
        backgrounds->setBombAnimation(window);
    if(backgrounds->explosionTime == true) //When its time for the explosion it will trigger the animation function
        backgrounds->setExplosionAnimation(window);
    backgrounds->enemyMovement();
    window.draw(backgrounds->enemsp[0]);
    window.draw(backgrounds->enemsp[1]);
    window.draw(backgrounds->enemsp[2]);
    window.draw(backgrounds->bombermansp);
    if(backgrounds->topBlockDestroyed == true) //If top explosion hits the block it will show that blocks animation
        backgrounds->setBlockDestructionAnimation(window,backgrounds->topBlockIndex);
    if(backgrounds->bottomBlockDestroyed == true) //If bottom explosion hits a block it will explode that block
        backgrounds->setBlockDestructionAnimation(window,backgrounds->bottomBlockIndex);
    if(backgrounds->leftBlockDestroyed == true)
        backgrounds->setBlockDestructionAnimation(window,backgrounds->leftBlockIndex);
    if(backgrounds->rightBlockDestroyed == true)
        backgrounds->setBlockDestructionAnimation(window,backgrounds->rightBlockIndex);
    if(backgrounds->showdeath == true) //If bomberman hit an enemy it will trigger the animation death, which then needs to be drawn to the window
        backgrounds->deathAnimation(window);
    if(backgrounds->showenemydeath == true) //If explosion collides with enemy one show its death animation
        backgrounds->setEnemyDeathAnimation(window);
    if(backgrounds->showenemydeath1 == true) //If explosion collides with enemy two show its death animation
        backgrounds->setEnemy1DeathAnimation(window);
    if(backgrounds->showenemydeath2 == true) //If explosion collides with enemy three show its death animation
        backgrounds->setEnemy2DeathAnimation(window);
    if(backgrounds->dead == true) //If bomberman died, this function simply deducts the player's lives
        backgrounds->deductLife();
    if(backgrounds->numLives == 0) //If the player runs out of lives, the game will display to the user the Game Over sprite
    {
        window.draw(backgrounds->gameoversp);
        window.draw(backgrounds->cont);
    }
    if(backgrounds->win == true) //If the player reaches the gate then bomberman wins
    {
        window.draw(backgrounds->victory);
        window.draw(backgrounds->cont);
    }
}

void Bomberman::exit()
{
    backgrounds->bm_music.stop();
}
