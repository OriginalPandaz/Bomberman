#ifndef SPRITES_H
#define SPRITES_H
#include <SFML/Graphics.hpp>

class Sprites
{
public:
    Sprites();
    void setTextures();
    void setSprites();

public:
    sf::Texture bombermantex;
    sf::Texture bombtex;
    sf::Texture blocktex[3];
    sf::Texture block_dtex[7];
    sf::Texture bmdeath_tex[8];
    sf::Texture explosion_c_tex;
    sf::Texture explosion_u_tex;
    sf::Texture explosion_d_tex;
    sf::Texture explosion_r_tex;
    sf::Texture explosion_l_tex;
    sf::Texture enemtex[5];

private:
    sf::Texture border[4];
    sf::Texture windowtex;
    sf::Texture gameovertex;
    sf::Texture gatetex;

public:
    sf::Sprite windowsp;
    sf::Sprite bordersp[4];
    sf::Sprite gameoversp;
    sf::Sprite bombermansp;
    sf::Sprite bombsp;
    sf::Sprite enemsp[3];
    sf::Sprite explosion_c_sp;
    sf::Sprite explosion_u_sp;
    sf::Sprite explosion_d_sp;
    sf::Sprite explosion_r_sp;
    sf::Sprite explosion_l_sp;
    sf::Sprite block_dsp[7];
protected:
    sf::Sprite blocksp[3];
    sf::Sprite blocker[30];
    sf::Sprite bomberman_dsp[8];
    sf::Vector2f origin;
    sf::Sprite gatesp;
};

#endif // SPRITES_H
