#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Bomberman/sprites.h"
#include "../Bomberman/Collision.h"

class Background : public Sprites
{
public:
    Background();
    void randomizeBlocks();
    void getNumBlocks();
    void drawBlocks(sf::RenderTarget &window);
    void setDefaultEnemyPos();
    void setExplosionPos();
    void setTimer();
    void setLives();
    void setScores();
    void setSounds();
    void setFonts();
    void addScores();
    void CheckBorderCollision();
    void CheckEnemyCollision();
    void CheckBlockerCollision();
    void CheckBlocksCollision();
    void CheckBombCollision();
    void CheckExplosionCollision();
    void CheckGateCollision();
    void setDefaultAnimation();
    void deathAnimation(sf::RenderTarget &window);
    void setBombAnimation(sf::RenderTarget & window);
    void setExplosionAnimation(sf::RenderTarget& window);
    void setEnemyDeathAnimation(sf::RenderTarget &window);
    void setEnemy1DeathAnimation(sf::RenderTarget &window);
    void setEnemy2DeathAnimation(sf::RenderTarget &window);
    void setBlocktoGrass(int &index);
    void setBlockDestructionAnimation(sf::RenderTarget &window, int& i);
    void enemyMovement();
    void enemyChangeDirection();
    void enemy1ChangeDirection();
    void enemy2ChangeDirection();
    void deductLife();
    void restartGame();

public:
    bool checkTimer = false, up = false, down = false, left = false, right = false;
    bool dead = false, showdeath = false, collidable = true, killable = true, killable1 = true, killable2 = true, addscore = false, addscore1 = false, addscore2 = false;
    bool showenemydeath = false, showenemydeath1 = false, showenemydeath2 = false;
    bool onBomb = true, bombPlaced = false, explosionTime = false, explodable = true, win = false;
    bool bottomBlockDestroyed = false, topBlockDestroyed = false, leftBlockDestroyed = false, rightBlockDestroyed = false;
    bool enemLeft[3] = {false, false, false}, enemRight[3] = {true,false,false}, enemUp[3] = {false,false,true}, enemDown[3] = {false,true,false};
    float enemMovex = 0.5, enemMove1x = 0, enemMove2x = 0, enemMovey = 0, enemMove1y = 0.5, enemMove2y = -0.5;
    int mins = 4, numLives = 3, hiScore = 0, newScore = 0, reverse = 2;
    int gate = 0, gate_c = 0, gate_r = 0, numBlocks = 0;
    int index = 0, counter = 0, bombindex = 0, bombcounter = 0, explosionindex = 0, explosioncounter = 0;
    int enemyd_index = 0, enemyd_counter = 0, enemyd1_index = 0, enemyd1_counter = 0, enemyd2_index = 0, enemyd2_counter = 0;
    int blockd_index = 0, blockd_counter = 0;
    int bottomBlockIndex = -1, topBlockIndex = -1, leftBlockIndex = -1, rightBlockIndex = -1;
    int level[11][13] = {
        { 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0 },
        { 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0 },
        { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0 },
        { 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 0 },
        { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 2, 1, 2, 0, 2, 1, 2, 0, 2, 0, 2, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 2, 0, 2, 0, 2, 0, 2, 0, 2, 1, 2, 0 },
        { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 }};

public:
    sf::Text lives, clocktext, score, hiScores, victory, cont;
    sf::Sprite *blocks;
    sf::Clock clock;
    sf::Time timer;
    sf::Music bm_music;

private:
    sf::Clock deathClock;
    sf::Time deathTime;
    sf::SoundBuffer bomb_buff, bmdeath_buff;
    sf::Sound bomb_sound, bmdeath_sound;
    sf::Font font;
};

#endif // BACKGROUND_H
