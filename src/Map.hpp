/*
 * Copyright (c) 2011 Josh Koch <jdk1337@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 */

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Map
{
public:
    Map(sf::RenderWindow& app, sf::View& gView, std::string mapFileName);
    ~Map();
    void Update(const float& dt);
    void DrawBG();
    void DrawFG();

private:
    sf::RenderWindow* appP;
    sf::View* gViewP;

    unsigned short* BGtMap;
    unsigned short* FGtMap;
    sf::IntRect* rectMap;
    unsigned short mapWidth, mapHeight;
    sf::Image imgTileSet;
    sf::Sprite sprTile;
    sf::Music musBGM;

    void DrawLayer(unsigned short* layerTMap);
};

#endif
