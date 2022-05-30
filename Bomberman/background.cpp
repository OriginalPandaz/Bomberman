#include "../Bomberman/background.h"
#include <iostream>

using namespace std;
using namespace Collision;

Background::Background() //Constructor is called when class object is made in bomberman and calls these functions
{
    setSprites();
    setFonts();
    randomizeBlocks();
    getNumBlocks();
}

void Background::randomizeBlocks()
{
    //Randomizes the grass slots and block slots to turn either to a block or grass
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i<11; i++)
    {
        for (int j = 0; j<13; j++)
        {
            if (level[i][j] == 0 || level[i][j] == 1)
                level[i][j] = rand() % 2;
        }
    }
    //Sets the enemies and bombermans locations to grass so there is a clear path to move and they do not spawn in a block
    level[0][0] = 0;
    level[0][1] = 0;
    level[1][0] = 0;

    level[0][2] = 0;
    level[1][2] = 0;
    level[2][2] = 0;
    level[3][2] = 0;

    level[6][10] = 0;
    level[7][10] = 0;
    level[8][10] = 0;

    level[6][1] = 0;
    level[6][2] = 0;
    level[6][3] = 0;

    for (int i = 0; i<11; i++)
    {
        for (int j = 0; j<13; j++)
        {
            i = rand() % 11 + 0; //Randomizes through columns and rows to find a spot for the gate or exit
            j = rand() % 13 + 0;
            if (level[i][j] == 1)
            {
                gate_r = i;
                gate_c = j;
                cout << i << j;
                break;
            }
        }
        if (level[gate_r][gate_c] == 1) //If the randomized location is under a block then break otherwise
            break;                      //if we reach the end of column we put the gate in the first row with a location of the block
        else if (i == 10)
        {
            i = 0;
        }
    }
}

void Background::getNumBlocks() //Gets the value for amount of orange block sprites needed
{
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 13; j++)
            if (level[i][j] == 1)
                numBlocks++;
    }
    blocks = new sf::Sprite[numBlocks];
    for(int i = 0; i < numBlocks; i++)
        blocks[i].scale(1.5f,1.5);
}

void Background::drawBlocks(sf::RenderTarget &window)
{
    int blockercount = 0, blockscounter = 0;
    double blocklength = 248, blockwidth = 471; //These values represent the individual float positions that I had to mess around with
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 13; j++) //These two for loops are to cycle through the 2D array and set each position to its block sprite
        {
            blocksp[level[i][j]].setPosition(static_cast<float>(blockwidth),static_cast<float>(blocklength));
            if(i == 0 && j == 0)
                origin = blocksp[0].getPosition();
            if (i == gate_r && j == gate_c)
            {
                gatesp.setPosition(static_cast<float>(blockwidth+2),static_cast<float>(blocklength+2));
            }
            if(level[i][j] == 1)
            {
                (blocks + blockscounter)->setTexture(blocktex[1]);
                (blocks+blockscounter)->setPosition(static_cast<float>(blockwidth),static_cast<float>(blocklength));
                //                window.draw(*(blocks+blockscounter));
                blockscounter++;
            }
            if(level[i][j] == 2)
            {
                blocker[blockercount].setPosition(static_cast<float>(blockwidth),static_cast<float>(blocklength));
                //                window.draw(blocker[blockercount]);
                blockercount++;
            }
            if(gate == 1)
                window.draw(gatesp);
            window.draw(blocksp[level[i][j]]);
            blockwidth += 75.04;
        }
        blockwidth = 471; //Resets the x value to the left edge of the window
        blocklength += 64.4; //Increments the y value to go down
    }
}

void Background::setDefaultEnemyPos()
{
    enemsp[0].setPosition(631.08f,446.2f);
    enemsp[1].setPosition(706.12f,639.4f);
    enemsp[2].setPosition(1231.4f,703.8f);
}

void Background::setExplosionPos()
{
    explosion_c_sp.setPosition(bombsp.getPosition().x, bombsp.getPosition().y);
    explosion_u_sp.setPosition(bombsp.getPosition().x, bombsp.getPosition().y - + 57.8f);
    explosion_d_sp.setPosition(bombsp.getPosition().x, bombsp.getPosition().y + 57.8f);
    explosion_l_sp.setPosition(bombsp.getPosition().x - 68, bombsp.getPosition().y);
    explosion_r_sp.setPosition(bombsp.getPosition().x + 68, bombsp.getPosition().y);
    bombsp.setPosition(-100,-100);
}

void Background::setTimer()
{
    timer = clock.getElapsedTime(); //Set my time to the clocks timer
    int secs = 60 - (static_cast<int>(timer.asSeconds())); //The timer will subtract a second from 60 determining the new time
    if(secs == 60) //If the timer is barely starting set it to 4:00 rather than 4:60
    {
        clocktext.setString(to_string(mins) + ":" + "00");
    }
    else if(secs == 59 && checkTimer == false) //Once its no longer 00 the timer must lose a minute
    {
        mins -= 1;
        checkTimer = true;
    }
    else if(secs < 10 && secs > 0) //Checks if the value of the timer is single digit
        clocktext.setString(to_string(mins) + ":0" + to_string(secs));
    else if(secs >= 10) //Otherwise just display new time
        clocktext.setString(to_string(mins) + ":" + to_string(secs));
    if(static_cast<int>(timer.asSeconds()) >= 60) //If the timer reaches 1 minute it must be restarted
    {
        timer = clock.restart();
        checkTimer = false;
    }
    if(mins == 0 && secs == 0) //If out of time then bomberman dies and level restarts
    {
        restartGame();
        timer = clock.restart();
    }
}

void Background::setLives()
{
    lives.setString(to_string(numLives)); //Sets the Lives text font to the number of lives remaining
}

void Background::setScores()
{
    score.setString(to_string(newScore)); //Sets the Scores and HiScores values to whatever the score of the game is
    hiScores.setString(to_string(hiScore));
}

void Background::setSounds()
{
    //Ensuring the sound files are opened and setting the buffers to sounds
    if(!bm_music.openFromFile("Bomberman/music/Bomberman.wav"))
    {
        cout << "The music file was not found!\n";
    }
    if(!bomb_buff.loadFromFile("Bomberman/sound/bomb.wav"))
    {
        cout << "The bomb sound was not found!\n";
    }
    if(!bmdeath_buff.loadFromFile("Bomberman/sound/die.wav"))
    {
        cout << "The bomberman death sound was not found!\n";
    }
    bomb_sound.setBuffer(bomb_buff);
    bmdeath_sound.setBuffer(bmdeath_buff);
    bm_music.play();
    bm_music.setLoop(true);
}

void Background::setFonts()
{
    //Open the font file and set the font for all the different texts
    if(!font.loadFromFile("Bomberman/fonts/Perfect.ttf"))
        cout << "The font was not opened!\n";
    lives.setFont(font);
    lives.setFillColor(sf::Color::White);
    lives.setCharacterSize(45);
    clocktext.setFont(font);
    clocktext.setFillColor(sf::Color::White);
    clocktext.setCharacterSize(45);
    score.setFont(font);
    score.setFillColor(sf::Color::White);
    score.setCharacterSize(45);
    hiScores.setFont(font);
    hiScores.setFillColor(sf::Color::White);
    hiScores.setCharacterSize(45);
    victory.setFont(font);
    victory.setFillColor(sf::Color::Yellow);
    victory.setCharacterSize(300);
    victory.setString("VICTORY");
    victory.setStyle(sf::Text::Bold);
    cont.setFont(font);
    cont.setCharacterSize(50);
    cont.setFillColor(sf::Color::White);
    cont.setString("Press Enter to Continue Playing!");
    cont.setStyle(sf::Text::Bold);
}

void Background::addScores()
{
    score.setPosition(600,113);
    hiScores.setPosition(1350,113);
    srand(static_cast<unsigned int>(time(nullptr)));
    if(addscore == true) //If an enemy dies it will add score to the new score with a random number
    {
        int random = rand()%8000+2365913;
        newScore += random;
        if(newScore > hiScore)
            hiScore = newScore;
        addscore = false;
    }
    if(addscore1 == true)
    {
        int random = rand()%8000+2365913;
        newScore += random;
        if(newScore > hiScore)
            hiScore = newScore;
        addscore1 = false;
    }
    if(addscore2 == true)
    {
        int random = rand()%8000+2365913;
        newScore += random;
        if(newScore > hiScore)
            hiScore = newScore;
        addscore2 = false;
    }
}

void Background::CheckBorderCollision()
{
    if(PixelPerfectTest(bombermansp,bordersp[0]) || PixelPerfectTest(bombermansp,bordersp[1]) || PixelPerfectTest(bombermansp,bordersp[2])
            || PixelPerfectTest(bombermansp,bordersp[3]))
    {
        reverse = 2;
        setDefaultAnimation();
    }
    if(PixelPerfectTest(enemsp[0],bordersp[0]) || PixelPerfectTest(enemsp[0],bordersp[1]) || PixelPerfectTest(enemsp[0],bordersp[2])
            || PixelPerfectTest(enemsp[0],bordersp[3]))
    {
        enemyChangeDirection();
    }
    if(PixelPerfectTest(enemsp[1],bordersp[0]) || PixelPerfectTest(enemsp[1],bordersp[1]) || PixelPerfectTest(enemsp[1],bordersp[2])
            || PixelPerfectTest(enemsp[1],bordersp[3]))
    {
        enemy1ChangeDirection();
    }
    if(PixelPerfectTest(enemsp[2],bordersp[0]) || PixelPerfectTest(enemsp[2],bordersp[1]) || PixelPerfectTest(enemsp[2],bordersp[2])
            || PixelPerfectTest(enemsp[2],bordersp[3]))
    {
        enemy2ChangeDirection();
    }
    if(PixelPerfectTest(explosion_l_sp,bordersp[0]) || PixelPerfectTest(explosion_l_sp,bordersp[1]) || PixelPerfectTest(explosion_l_sp,bordersp[2])
            || PixelPerfectTest(explosion_l_sp,bordersp[3]))
    {
        explosion_l_sp.setPosition(-100,-100);
    }
    if(PixelPerfectTest(explosion_r_sp,bordersp[0]) || PixelPerfectTest(explosion_r_sp,bordersp[1]) || PixelPerfectTest(explosion_r_sp,bordersp[2])
            || PixelPerfectTest(explosion_r_sp,bordersp[3]))
    {
        explosion_r_sp.setPosition(-100,-100);
    }
    if(PixelPerfectTest(explosion_u_sp,bordersp[0]) || PixelPerfectTest(explosion_u_sp,bordersp[1]) || PixelPerfectTest(explosion_u_sp,bordersp[2])
            || PixelPerfectTest(explosion_u_sp,bordersp[3]))
    {
        explosion_u_sp.setPosition(-100,-100);
    }
    if(PixelPerfectTest(explosion_d_sp,bordersp[0]) || PixelPerfectTest(explosion_d_sp,bordersp[1]) || PixelPerfectTest(explosion_d_sp,bordersp[2])
            || PixelPerfectTest(explosion_d_sp,bordersp[3]))
    {
        explosion_d_sp.setPosition(-100,-100);
    }
}

void Background::CheckEnemyCollision()
{
    if(PixelPerfectTest(bombermansp,enemsp[0]) || (PixelPerfectTest(bombermansp,enemsp[1]) || (PixelPerfectTest(bombermansp,enemsp[2]))))
    {                                   //Checks if bomberman sprite touches the 3 enemy sprites
        if(collidable == true)
        {
            showdeath = true;
            dead = true;
            collidable = false;
        }
    }
}

void Background::CheckBlockerCollision()
{
    for(int i = 0; i < 30; i++){
        if(PixelPerfectTest(bombermansp, blocker[i])) //Check if the gray blocks are collided by bomberman
        {
            reverse = 2;
            setDefaultAnimation();
        }
        if(PixelPerfectTest(enemsp[0], blocker[i]))
        {
            enemyChangeDirection();
        }
        if(PixelPerfectTest(enemsp[1],blocker[i]))
        {
            enemy1ChangeDirection();
        }
        if(PixelPerfectTest(enemsp[2],blocker[i]))
        {
            enemy2ChangeDirection();
        }
    }
}

void Background::CheckBlocksCollision()
{
    for(int i = 0; i < numBlocks; i++){
        if(PixelPerfectTest(bombermansp, blocks[i])) //Checks if the generated orange blocks touch bomberman
        {
            reverse = 2;
            setDefaultAnimation();
        }
        if(PixelPerfectTest(enemsp[0], blocks[i]))
        {
            enemyChangeDirection();
        }
        if(PixelPerfectTest(enemsp[1],blocks[i]))
        {
            enemy1ChangeDirection();
        }
        if(PixelPerfectTest(enemsp[2],blocks[i]))
        {
            enemy2ChangeDirection();
        }
    }
}

void Background::CheckBombCollision()
{
    if(PixelPerfectTest(bombermansp,bombsp) && onBomb == true) //If bomberman barely plants the bomb this function runs to get him off bomb
    {
        reverse = 0;
        setDefaultAnimation();
    }
    if(!PixelPerfectTest(bombermansp,bombsp))
    {
        onBomb = false;
    }
    if(PixelPerfectTest(bombermansp,bombsp) && onBomb == false) //This function knows he is not off the bomb so he gets blocked by the bomb
    {
        reverse = 2;
        setDefaultAnimation();
    }
    if(PixelPerfectTest(enemsp[0], bombsp))
    {
        enemyChangeDirection();
    }
    if(PixelPerfectTest(enemsp[1],bombsp))
    {
        enemy1ChangeDirection();
    }
    if(PixelPerfectTest(enemsp[2],bombsp))
    {
        enemy2ChangeDirection();
    }

}

void Background::CheckExplosionCollision()
{
    if(PixelPerfectTest(bombermansp,explosion_c_sp) || PixelPerfectTest(bombermansp,explosion_d_sp) || PixelPerfectTest(bombermansp,explosion_l_sp)
            || PixelPerfectTest(bombermansp,explosion_r_sp) || PixelPerfectTest(bombermansp,explosion_u_sp)) //Checks if bomberman is hit by explosion
    {
        if(explodable == true)
        {
            showdeath = true;
            dead = true;
            explodable = false;
        }
    }
    if(PixelPerfectTest(enemsp[0],explosion_c_sp) || PixelPerfectTest(enemsp[0], explosion_d_sp) || PixelPerfectTest(enemsp[0],explosion_u_sp)
            || PixelPerfectTest(enemsp[0],explosion_l_sp) || PixelPerfectTest(enemsp[0],explosion_r_sp)) //Checks if enemy is hit by explosion
    {
        if(killable == true)
        {
            showenemydeath = true;
            addscore = true;
        }
    }
    if(PixelPerfectTest(enemsp[1],explosion_c_sp) || PixelPerfectTest(enemsp[1], explosion_d_sp) || PixelPerfectTest(enemsp[1],explosion_u_sp)
            || PixelPerfectTest(enemsp[1],explosion_l_sp) || PixelPerfectTest(enemsp[1],explosion_r_sp))
    {
        if(killable1 == true)
        {
            showenemydeath1 = true;
            addscore1 = true;
        }
    }
    if(PixelPerfectTest(enemsp[2],explosion_c_sp) || PixelPerfectTest(enemsp[2], explosion_d_sp) || PixelPerfectTest(enemsp[2],explosion_u_sp)
            || PixelPerfectTest(enemsp[2],explosion_l_sp) || PixelPerfectTest(enemsp[2],explosion_r_sp))
    {
        if(killable2 == true)
        {
            showenemydeath2 = true;
            addscore2 = true;
        }
    }
    for(int i = 0; i < numBlocks; i++){
        if(PixelPerfectTest(blocks[i], explosion_d_sp)) //Determines which explosion hits the orange blocks
        {
            bottomBlockIndex = i;
            bottomBlockDestroyed = true;
        }
        if(PixelPerfectTest(blocks[i],explosion_u_sp))
        {
            topBlockIndex = i;
            topBlockDestroyed = true;
        }
        if(PixelPerfectTest(blocks[i],explosion_l_sp))
        {
            leftBlockIndex = i;
            leftBlockDestroyed = true;
        }
        if(PixelPerfectTest(blocks[i],explosion_r_sp))
        {
            rightBlockIndex = i;
            rightBlockDestroyed = true;
        }
    }
}

void Background::CheckGateCollision()
{
    for(int i = 0; i < numBlocks; i++)
        if(PixelPerfectTest(bombermansp,gatesp) && !PixelPerfectTest(bombermansp,blocks[i]))
        {
            win = true;
        }
}

void Background::setDefaultAnimation()
{
    if(left == true) //Sets character to basic left position
    {
        if(!bombermantex.loadFromFile("Bomberman/images/bm_left.png"))
        {
            cout << "The image with bomberman staring left was not found!\n";
        }
        bombermansp.setTexture(bombermantex);
        bombermansp.move(reverse,0);
        left = false;
    }
    if(right == true)
    {
        if(!bombermantex.loadFromFile("Bomberman/images/bm_right.png"))
        {
            cout << "The image with bomberman staring right was not found!\n";
        }
        bombermansp.setTexture(bombermantex);
        bombermansp.move(-reverse,0);
        right = false;
    }
    if(up == true)
    {
        if(!bombermantex.loadFromFile("Bomberman/images/bm_up.png"))
        {
            cout << "The image with bomberman staring up was not found!\n";
        }
        bombermansp.setTexture(bombermantex);
        bombermansp.move(0,reverse);
        up = false;
    }
    if(down == true)
    {
        if(!bombermantex.loadFromFile("Bomberman/images/bm.png"))
        {
            cout << "The image with bomberman staring right was not found!\n";
        }
        bombermansp.setTexture(bombermantex);
        bombermansp.move(0,-reverse);
        down = false;
    }
}

void Background::deathAnimation(sf::RenderTarget &window)
{
    bombermansp.setTexture(bmdeath_tex[index]);
    bomberman_dsp[index].setPosition(bombermansp.getPosition()); //Set death animation sprite to the character sprite
    window.draw(bomberman_dsp[index]);
    counter++; //Counter acts as a timer and adds up until it reaches 81, which increments timer to show the different images within the sprite array
    if(counter == 12)
        index++;
    else if(counter == 24)
        index++;
    else if(counter == 36)
        index++;
    else if(counter == 48)
        index++;
    else if(counter == 60)
    {
        bmdeath_sound.play();
        index++;
    }
    else if(counter == 72)
        index++;
    else if(counter == 81)
        index++;
    if(counter == 81)
    {
        showdeath = false;
        if(numLives > 0)
        {
            restartGame();
            timer = clock.restart();
            mins = 4;
            checkTimer = false;
        }
    }
}

void Background::setBombAnimation(sf::RenderTarget &window)
{
    bombcounter++; //Counter acts as a timer and adds up until it reaches 81, which increments timer to show the different images within the sprite array
    if(bombcounter == 50)
    {
        bombindex++;
        if(!bombtex.loadFromFile("Bomberman/images/bomb/bomb_2.png"))
        {
            cout << "Bomb picture was not found!\n";
        }
        bombsp.setTexture(bombtex);
    }
    else if(bombcounter == 100)
    {
        bombindex++;
        if(!bombtex.loadFromFile("Bomberman/images/bomb/bomb_3.png"))
        {
            cout << "Bomb picture was not found!\n";
        }
        bombsp.setTexture(bombtex);
    }
    else if(bombcounter == 150)
    {
        setExplosionPos();
        explosionTime = true;
        bomb_sound.play();
    }
    window.draw(bombsp);
}

void Background::setExplosionAnimation(sf::RenderTarget &window)
{
    explosioncounter++;
    if(explosioncounter == 8)
    {
        explosionindex++;
        if(!explosion_c_tex.loadFromFile("Bomberman/images/bomb/ex_center_1.png"))
        {
            cout << "First center explosion picture not found!\n";
        }
        explosion_c_sp.setTexture(explosion_c_tex);
        if(!explosion_u_tex.loadFromFile("Bomberman/images/bomb/ex_up_end_1.png"))
        {
            cout << "First upper explosion picture not found!\n";
        }
        explosion_u_sp.setTexture(explosion_u_tex);
        if(!explosion_d_tex.loadFromFile("Bomberman/images/bomb/ex_down_end_1.png"))
        {
            cout << "First bottom explosion picture not found!\n";
        }
        explosion_d_sp.setTexture(explosion_d_tex);
        if(!explosion_r_tex.loadFromFile("Bomberman/images/bomb/ex_right_end_1.png"))
        {
            cout << "First bottom explosion picture not found!\n";
        }
        explosion_r_sp.setTexture(explosion_r_tex);
        if(!explosion_l_tex.loadFromFile("Bomberman/images/bomb/ex_left_end_1.png"))
        {
            cout << "First bottom explosion picture not found!\n";
        }
        explosion_l_sp.setTexture(explosion_l_tex);
    }
    if(explosioncounter == 16)
    {
        explosionindex++;
        if(!explosion_c_tex.loadFromFile("Bomberman/images/bomb/ex_center_2.png"))
        {
            cout << "Second center explosion picture not found!\n";
        }
        explosion_c_sp.setTexture(explosion_c_tex);
        if(!explosion_u_tex.loadFromFile("Bomberman/images/bomb/ex_up_end_2.png"))
        {
            cout << "Second upper explosion picture not found!\n";
        }
        explosion_u_sp.setTexture(explosion_u_tex);
        if(!explosion_d_tex.loadFromFile("Bomberman/images/bomb/ex_down_end_2.png"))
        {
            cout << "Second bottom explosion picture not found!\n";
        }
        explosion_d_sp.setTexture(explosion_d_tex);
        if(!explosion_r_tex.loadFromFile("Bomberman/images/bomb/ex_right_end_2.png"))
        {
            cout << "Second right explosion picture not found!\n";
        }
        explosion_r_sp.setTexture(explosion_r_tex);
        if(!explosion_l_tex.loadFromFile("Bomberman/images/bomb/ex_left_end_2.png"))
        {
            cout << "Second left explosion picture not found!\n";
        }
        explosion_l_sp.setTexture(explosion_l_tex);
    }
    if(explosioncounter == 24)
    {
        explosionindex++;
        if(!explosion_c_tex.loadFromFile("Bomberman/images/bomb/ex_center_3.png"))
        {
            cout << "Third center explosion picture not found!\n";
        }
        explosion_c_sp.setTexture(explosion_c_tex);
        if(!explosion_u_tex.loadFromFile("Bomberman/images/bomb/ex_up_end_3.png"))
        {
            cout << "Third upper explosion picture not found!\n";
        }
        explosion_u_sp.setTexture(explosion_u_tex);
        if(!explosion_d_tex.loadFromFile("Bomberman/images/bomb/ex_down_end_3.png"))
        {
            cout << "Third bottom explosion picture not found!\n";
        }
        explosion_d_sp.setTexture(explosion_d_tex);
        if(!explosion_r_tex.loadFromFile("Bomberman/images/bomb/ex_right_end_3.png"))
        {
            cout << "Third right explosion picture not found!\n";
        }
        explosion_r_sp.setTexture(explosion_r_tex);
        if(!explosion_l_tex.loadFromFile("Bomberman/images/bomb/ex_left_end_3.png"))
        {
            cout << "Third left explosion picture not found!\n";
        }
        explosion_l_sp.setTexture(explosion_l_tex);
    }
    if(explosioncounter == 32)
    {
        explosionindex++;
        if(!explosion_c_tex.loadFromFile("Bomberman/images/bomb/ex_center_4.png"))
        {
            cout << "Fourth center explosion picture not found!\n";
        }
        explosion_c_sp.setTexture(explosion_c_tex);
        if(!explosion_u_tex.loadFromFile("Bomberman/images/bomb/ex_up_end_4.png"))
        {
            cout << "Fourth upper explosion picture not found!\n";
        }
        explosion_u_sp.setTexture(explosion_u_tex);
        if(!explosion_d_tex.loadFromFile("Bomberman/images/bomb/ex_down_end_4.png"))
        {
            cout << "Fourth bottom explosion picture not found!\n";
        }
        explosion_d_sp.setTexture(explosion_d_tex);
        if(!explosion_r_tex.loadFromFile("Bomberman/images/bomb/ex_right_end_4.png"))
        {
            cout << "Fourth right explosion picture not found!\n";
        }
        explosion_r_sp.setTexture(explosion_r_tex);
        if(!explosion_l_tex.loadFromFile("Bomberman/images/bomb/ex_left_end_4.png"))
        {
            cout << "Fourth left explosion picture not found!\n";
        }
        explosion_l_sp.setTexture(explosion_l_tex);
    }
    if(explosioncounter == 40)
    {
        explosion_c_sp.setPosition(-100,-100);
        explosion_u_sp.setPosition(-100,-100);
        explosion_d_sp.setPosition(-100,-100);
        explosion_l_sp.setPosition(-100,-100);
        explosion_r_sp.setPosition(-100,-100);
        explosioncounter = 0;
        explosionindex = 0;
        if(explosioncounter == 0)
            bombPlaced = false;
    }
    window.draw(explosion_c_sp);
    window.draw(explosion_u_sp);
    window.draw(explosion_d_sp);
    window.draw(explosion_l_sp);
    window.draw(explosion_r_sp);
}

void Background::setEnemyDeathAnimation(sf::RenderTarget &window) //Counts through the enemy death sprites and sets the enemy sprite to the death sprites
{
    enemMovex = 0;
    enemMovey = 0;
    enemyd_counter++;
    if(enemyd_counter == 10)
    {
        enemyd_index++;
        enemsp[0].setTexture(enemtex[enemyd_index]);
    }
    else if(enemyd_counter == 20)
    {
        enemyd_index++;
        enemsp[0].setTexture(enemtex[enemyd_index]);
    }
    else if(enemyd_counter == 30)
    {
        enemyd_index++;
        enemsp[0].setTexture(enemtex[enemyd_index]);
    }
    else if(enemyd_counter == 40)
    {
        enemyd_index++;
        enemsp[0].setTexture(enemtex[enemyd_index]);
    }
    else if(enemyd_counter == 50)
    {
        enemsp[0].setPosition(-100,-100);
        showenemydeath = false;
        killable = false;
        addScores();
    }
    window.draw(enemsp[0]);
}

void Background::setEnemy1DeathAnimation(sf::RenderTarget &window)
{
    enemMove1x = 0;
    enemMove1y = 0;
    enemyd1_counter++;
    if(enemyd1_counter == 10)
    {
        enemyd1_index++;
        enemsp[1].setTexture(enemtex[enemyd1_index]);
    }
    else if(enemyd1_counter == 20)
    {
        enemyd1_index++;
        enemsp[1].setTexture(enemtex[enemyd1_index]);
    }
    else if(enemyd1_counter == 30)
    {
        enemyd1_index++;
        enemsp[1].setTexture(enemtex[enemyd1_index]);
    }
    else if(enemyd1_counter == 40)
    {
        enemyd1_index++;
        enemsp[1].setTexture(enemtex[enemyd1_index]);
    }
    else if(enemyd1_counter == 50)
    {
        enemsp[1].setPosition(-100,-100);
        showenemydeath1 = false;
        killable1 = false;
        addScores();
    }
    window.draw(enemsp[1]);
}

void Background::setEnemy2DeathAnimation(sf::RenderTarget &window)
{
    enemMove2x = 0;
    enemMove2y = 0;
    enemyd2_counter++;
    if(enemyd2_counter == 10)
    {
        enemyd2_index++;
        enemsp[2].setTexture(enemtex[enemyd2_index]);
    }
    else if(enemyd2_counter == 20)
    {
        enemyd2_index++;
        enemsp[2].setTexture(enemtex[enemyd2_index]);
    }
    else if(enemyd2_counter == 30)
    {
        enemyd2_index++;
        enemsp[2].setTexture(enemtex[enemyd2_index]);
    }
    else if(enemyd2_counter == 40)
    {
        enemyd2_index++;
        enemsp[2].setTexture(enemtex[enemyd2_index]);
    }
    else if(enemyd2_counter == 50)
    {
        enemsp[2].setPosition(-100,-100);
        showenemydeath2 = false;
        killable2 = false;
        addScores();
    }
    window.draw(enemsp[2]);
}

void Background::setBlocktoGrass(int& index) //Checks which block was hit and tells drawBlocks to set that position as grass instead of a block
{
    int counter = 0;
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 13; j++)
        {
            if(level[i][j] == 1)
            {
                if(counter == index)
                {
                    level[i][j] = 0;
                    getNumBlocks();
                    if(i == gate_r && j == gate_c)
                        gate = 1;
                }
                counter++;
            }
        }
    }
}

void Background::setBlockDestructionAnimation(sf::RenderTarget &window, int &i)
{
    blockd_counter++;
    blocks[i].setTexture((block_dtex[blockd_index]));
    window.draw(blocks[i]);
    if(blockd_counter == 5)
    {
        blockd_index++;
    }
    else if(blockd_counter == 10)
    {
        blockd_index++;
    }
    else if(blockd_counter == 15)
    {
        blockd_index++;
    }
    else if(blockd_counter == 20)
    {
        blockd_index++;
    }
    else if(blockd_counter == 15)
    {
        blockd_index++;
    }
    else if(blockd_counter == 20)
    {
        blockd_index++;
    }
    else if(blockd_counter == 25)
    {
        setBlocktoGrass(i);
        blocks[i].setPosition(-200,-200);
        blockd_index = 0;
        blockd_counter = 0;
        bottomBlockDestroyed = false;
        topBlockDestroyed = false;
        leftBlockDestroyed = false;
        rightBlockDestroyed = false;
    }
}

void Background::enemyMovement()
{
    enemsp[0].move(enemMovex, enemMovey);
    enemsp[1].move(enemMove1x, enemMove1y);
    enemsp[2].move(enemMove2x, enemMove2y);
}

void Background::enemyChangeDirection()
{
    if(enemRight[0] == true) //If enemy goes right back them up and then make them go down
    {
        enemsp[0].move(-3,enemMovey);
        enemMovex = 0;
        enemMovey = 0.5;
        enemDown[0] = true;
        enemRight[0] = false;
    }
    else if(enemDown[0] == true) //If enemy is going down go left
    {
        enemsp[0].move(enemMovex, -3);
        enemMovex = -0.5;
        enemMovey = 0;
        enemLeft[0] = true;
        enemDown[0] = false;
    }
    else if(enemLeft[0] == true) //If enemy is going left make them go up
    {
        enemsp[0].move(3, enemMovey);
        enemMovex = 0;
        enemMovey = -0.5;
        enemUp[0] = true;
        enemLeft[0] = false;
    }
    else if(enemUp[0] == true) //If enemy is going up make them go left
    {
        enemsp[0].move(enemMovex, 3);
        enemMovex = 0.5;
        enemMovey = 0;
        enemRight[0] = true;
        enemUp[0] = false;
    }
}

void Background::enemy1ChangeDirection()
{
    if(enemRight[1] == true)
    {
        enemsp[1].move(-2,enemMove1x);
        enemMove1x = 0;
        enemMove1y = 0.5;
        enemRight[1] = false;
        enemDown[1] = true;
    }
    else if(enemDown[1] == true)
    {
        enemsp[1].move(enemMove1x,-2);
        enemMove1x = -0.5;
        enemMove1y = 0;
        enemDown[1] = false;
        enemLeft[1] = true;
    }
    else if(enemLeft[1] == true)
    {
        enemsp[1].move(2, enemMove1y);
        enemMove1x = 0;
        enemMove1y = -0.5;
        enemLeft[1] = false;
        enemUp[1] = true;
    }
    else if(enemUp[1] == true)
    {
        enemsp[1].move(enemMove1x, 2);
        enemMove1x = 0.5;
        enemMove1y = 0;
        enemUp[1] = false;
        enemRight[1] = true;
    }
}

void Background::enemy2ChangeDirection()
{
    if(enemRight[2] == true)
    {
        enemsp[2].move(-2,enemMove2y);
        enemMove2x = 0;
        enemMove2y = 0.5;
        enemRight[2] = false;
        enemDown[2] = true;
    }
    else if(enemDown[2] == true)
    {
        enemsp[2].move(enemMove2x,-2);
        enemMove2x = -0.5;
        enemMove2y = 0;
        enemDown[2] = false;
        enemLeft[2] = true;
    }
    else if(enemLeft[2] == true)
    {
        enemsp[2].move(2,enemMove2y);
        enemMove2x = 0;
        enemMove2y = -0.5;
        enemLeft[2] = false;
        enemUp[2] = true;
    }
    else if(enemUp[2] == true)
    {
        enemsp[2].move(enemMovex,2);
        enemMove2x = 0.5;
        enemMove2y = 0;
        enemUp[2] = false;
        enemRight[2] = true;
    }
}

void Background::deductLife()
{
    if(dead == true && numLives > 0) //After checking if bomberman touched an enemy, this will decrease his life as long as there are still lives remaining
    {
        numLives -= 1;
        setLives();
        dead = false;
    }
}


void Background::restartGame() //Create new block placements and characters back to default position and allows the bomberman sprite to collide with enemy
{
    randomizeBlocks();
    getNumBlocks();
    checkTimer = false;
    win = false;
    collidable = true;
    explodable = true;
    killable = true;
    killable1 = true;
    killable2 = true;
    for(int i = 0; i < 3; i++)
        enemLeft[i] = false;
    enemRight[0] = true;
    enemRight[1] = false;
    enemRight[2] = false;
    enemUp[0] = false;
    enemUp[1] = false;
    enemUp[2] = true;
    enemDown[0] = false;
    enemDown[1] = true;
    enemDown[2] = false;
    enemMovex = 0.5;
    enemMove1x = 0;
    enemMove2x = 0;
    enemMovey = 0;
    enemMove1y = 0.5;
    enemMove2y = -0.5;
    newScore = 0;
    gate = 0;
    counter = 0;
    index = 0;
    enemyd_index = 0;
    enemyd_counter = 0;
    enemyd1_index = 0;
    enemyd1_counter = 0;
    enemyd2_index = 0;
    enemyd2_counter = 0;
    mins = 4;
    score.setPosition(750,113);
    if(hiScore == 0)
        hiScores.setPosition(1500,113);
    bombsp.setPosition(-100,-100);
    explosion_c_sp.setPosition(-100,-100);
    explosion_u_sp.setPosition(-100,-100);
    explosion_d_sp.setPosition(-100,-100);
    explosion_l_sp.setPosition(-100,-100);
    explosion_r_sp.setPosition(-100,-100);
    bombermansp.setPosition(origin);
    bombermansp.setTexture(bombermantex);
    enemsp[0].setTexture(enemtex[0]);
    enemsp[1].setTexture(enemtex[0]);
    enemsp[2].setTexture(enemtex[0]);
    setDefaultEnemyPos();
}
