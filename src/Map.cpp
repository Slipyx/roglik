/*
 * roglik - Map.cpp
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

#include "Map.hpp"

const unsigned char TILE_SIZE = 32;

Map::Map(sf::RenderWindow& app)
{
    appP = &app;
    mapWidth = 250;
    mapHeight = 250;
    imgTileSet.LoadFromFile("images/tile.png");
    imgTileSet.SetSmooth(false);
    sprTile.SetImage(imgTileSet);
    // Load tMap
    tMap = new unsigned short[mapWidth * mapHeight];
    for(int ty = 0; ty < mapHeight; ty++)
    {
        for(int tx = 0; tx < mapWidth; tx++)
        {
            if(sf::Randomizer::Random(0.0f, 1.0f) <= 0.5f)
                tMap[ty * TILE_SIZE + tx] = 1;
            else
                tMap[ty * TILE_SIZE + tx] = 0;
        }
    }
}

void Map::Update(const float& dt)
{
}

void Map::Draw()
{
    sf::Vector2f gameViewCenter = appP->GetView().GetCenter();
    float tileRenderSpaceHalfWidth = ((appP->GetWidth() / 2.0f) + TILE_SIZE);
    float tileRenderSpaceHalfHeight = ((appP->GetHeight() / 2.0f) + TILE_SIZE);
    for(int ty = 0; ty < mapHeight; ty++)
    {
        for(int tx = 0; tx < mapWidth; tx++)
        {
            // If tile is within game view
            if(tx * TILE_SIZE > gameViewCenter.x - tileRenderSpaceHalfWidth &&
               tx * TILE_SIZE < gameViewCenter.x + tileRenderSpaceHalfWidth &&
               ty * TILE_SIZE > gameViewCenter.y - tileRenderSpaceHalfHeight &&
               ty * TILE_SIZE < gameViewCenter.y + tileRenderSpaceHalfHeight)
            {
                if(tMap[ty * TILE_SIZE + tx])
                {
                    sprTile.SetPosition(tx * TILE_SIZE, ty * TILE_SIZE);
                    appP->Draw(sprTile);
                }
            }
        }
    }
}

Map::~Map()
{
    delete[] tMap;
}