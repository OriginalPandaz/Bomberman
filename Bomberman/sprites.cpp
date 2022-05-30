#include "../Bomberman/sprites.h"
#include <iostream>

using namespace std;
Sprites::Sprites()
{

}

void Sprites::setTextures()
{
    //Acquring the textures of the images that are fixed and used for animations
    if(!bombermantex.loadFromFile("Bomberman/images/bm.png"))
    {
        cout << "Bomberman character texture not found!\n";
    }
    if(!blocktex[0].loadFromFile("Bomberman/images/grass.png"))
    {
        cout << "The grass texture was not found!\n";
    }
    if(!blocktex[1].loadFromFile("Bomberman/images/wall.png"))
    {
        cout << "The wall texture was not found!\n";
    }
    if(!blocktex[2].loadFromFile("Bomberman/images/block.png"))
    {
        cout << "The block texture was not found!\n";
    }
    if(!block_dtex[0].loadFromFile("Bomberman/images/blocks/des_1.png"))
    {
        cout << "The first block destruction texture was not found!\n";
    }
    if(!block_dtex[1].loadFromFile("Bomberman/images/blocks/des_2.png"))
    {
        cout << "The second block destruction texture was not found!\n";
    }
    if(!block_dtex[2].loadFromFile("Bomberman/images/blocks/des_3.png"))
    {
        cout << "The third block destruction texture was not found!\n";
    }
    if(!block_dtex[3].loadFromFile("Bomberman/images/blocks/des_4.png"))
    {
        cout << "The foruth block destruction texture was not found!\n";
    }
    if(!block_dtex[4].loadFromFile("Bomberman/images/blocks/des_5.png"))
    {
        cout << "The fifth block destruction texture was not found!\n";
    }
    if(!block_dtex[5].loadFromFile("Bomberman/images/blocks/des_6.png"))
    {
        cout << "The sixth block destruction texture was not found!\n";
    }
    if(!block_dtex[6].loadFromFile("Bomberman/images/blocks/des_7.png"))
    {
        cout << "The seventh block destruction texture was not found!\n";
    }
    if(!enemtex[0].loadFromFile("Bomberman/images/Enemies/1.png"))
    {
        cout << "The first enemy image was not found!\n";
    }
    if(!enemtex[1].loadFromFile("Bomberman/images/Enemies/2.png"))
    {
        cout << "The second enemy image was not found!\n";
    }
    if(!enemtex[2].loadFromFile("Bomberman/images/Enemies/3.png"))
    {
        cout << "The third enemy image was not found!\n";
    }
    if(!enemtex[3].loadFromFile("Bomberman/images/Enemies/4.png"))
    {
        cout << "The fourth enemy image was not found!\n";
    }
    if(!enemtex[4].loadFromFile("Bomberman/images/Enemies/5.png"))
    {
        cout << "The fifth enemy image was not found!\n";
    }
    if(!bmdeath_tex[0].loadFromFile("Bomberman/images/bm_d_1.png"))
    {
        cout << "The first bomberman death texture not found!\n";
    }
    if(!bmdeath_tex[1].loadFromFile("Bomberman/images/bm_d_2.png"))
    {
        cout << "The second bomberman death texture not found!\n";
    }
    if(!bmdeath_tex[2].loadFromFile("Bomberman/images/bm_d_3.png"))
    {
        cout << "The third bomberman death texture not found!\n";
    }
    if(!bmdeath_tex[3].loadFromFile("Bomberman/images/bm_d_4.png"))
    {
        cout << "The fourth bomberman death texture not found!\n";
    }
    if(!bmdeath_tex[4].loadFromFile("Bomberman/images/bm_d_5.png"))
    {
        cout << "The fifth bomberman death texture not found!\n";
    }
    if(!bmdeath_tex[5].loadFromFile("Bomberman/images/bm_d_6.png"))
    {
        cout << "The sixth bomberman death texture not found!\n";
    }
    if(!bmdeath_tex[6].loadFromFile("Bomberman/images/bm_d_7.png"))
    {
        cout << "The seventh bomberman death texture not found!\n";
    }
    if(!bmdeath_tex[7].loadFromFile("Bomberman/images/bm_d_8.png"))
    {
        cout << "The eight bomberman death texture not found!\n";
    }
    if(!windowtex.loadFromFile("Bomberman/images/window.png"))
    {
        cout << "The window texture was not found!\n";
    }
    if(!gameovertex.loadFromFile("Bomberman/images/gameover.png"))
    {
        cout << "The gameover texture was not found!\n";
    }
    if(!gatetex.loadFromFile("Bomberman/images/gate.png"))
    {
        cout << "The gate texture was not found!\n";
    }
    if(!border[0].loadFromFile("Bomberman/images/borderU.png"))
    {
        cout << "The upper border texture was not found!\n";
    }
    if(!border[1].loadFromFile("Bomberman/images/borderD.png"))
    {
        cout << "The bottom border texture was not found!\n";
    }
    if(!border[2].loadFromFile("Bomberman/images/borderR.png"))
    {
        cout << "The right border texture was not found!\n";
    }
    if(!border[3].loadFromFile("Bomberman/images/borderL.png"))
    {
        cout << "The left border texture was not found!\n";
    }
}

void Sprites::setSprites()
{
    //Setting the sprites using the textures
    setTextures();
    bombermansp.setTexture(bombermantex);
    bombermansp.scale(1.1f,1.1f);
    bombermansp.setPosition(471,248);
    for(int i = 0; i < 4; i++)
        bordersp[i].setTexture(border[i]);
    for(int i = 0; i < 3; i++)
    {
        blocksp[i].setTexture(blocktex[i]);
        blocksp[i].scale(1.5,1.5);
        blocktex->setSmooth(true);
    }
    for(int i = 0; i < 7; i++)
    {
        block_dsp[i].setTexture(block_dtex[i]);
        block_dsp[i].scale(1.5,1.5);
    }
    for(int i = 0; i < 3; i++)
    {
        enemsp[i].setTexture(enemtex[0]);
        enemsp[i].scale(1.15f,1.15f);
    }
    for(int i = 0; i < 8; i++)
    {
        bomberman_dsp[i].setTexture(bmdeath_tex[i]);
        bomberman_dsp[i].scale(1.15f,1.15f);
    }
    for(int i = 0; i < 30; i++)
    {
        blocker[i].scale(1.5f,1.5f);
        blocker[i].setTexture(blocktex[2]);
    }
    bombsp.scale(1.35f,1.35f);
    explosion_c_sp.scale(1.35f,1.35f);
    explosion_u_sp.scale(1.35f,1.35f);
    explosion_d_sp.scale(1.35f,1.35f);
    explosion_l_sp.scale(1.35f,1.35f);
    explosion_r_sp.scale(1.35f,1.35f);
    windowsp.setTexture(windowtex);
    windowsp.scale(1.5,1.5);
    gameoversp.setTexture(gameovertex);
    gameoversp.scale(1.75f,1.75f);
    gatesp.setTexture(gatetex);
    gatesp.scale(1.4f,1.4f);
}
