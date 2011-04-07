/*
 * roglik - Map.hpp
 * Copyright (C) 2011  Josh Koch <jdk1337@gmail.com>
 *
 * roglik is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * roglik is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with roglik.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

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
};

#endif
