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
#include <iostream>
#include "irrxml/irrXML.h"

const unsigned char TILE_SIZE = 16;

Map::Map(sf::RenderWindow& app, sf::View& gView, std::string mapFileName)
{
    sf::Clock mapLoadTimer;
    appP = &app;
    gViewP = &gView;
    // XML parser object for map file
    irr::io::IrrXMLReader* xml = irr::io::createIrrXMLReader(("maps/" + mapFileName).c_str());
    std::string BGtData;
    std::string FGtData;
    // ********************************
    // Parse the map file!
    while(xml && xml->read())
    {
        switch(xml->getNodeType())
        {
        case irr::io::EXN_ELEMENT:
            if(!strcmp("map", xml->getNodeName()))
            {
                mapWidth = xml->getAttributeValueAsInt("width");
                mapHeight = xml->getAttributeValueAsInt("height");
            }
            else if(!strcmp("music", xml->getNodeName()))
            {
                std::string musicFile = xml->getAttributeValue("file");
                musBGM.OpenFromFile("music/" + musicFile);
                musBGM.SetLoop(true);
            }
            else if(!strcmp("tileset", xml->getNodeName()))
            {
                std::string tilesetFile = xml->getAttributeValue("image");
                imgTileSet.LoadFromFile("images/" + tilesetFile);
                sprTile.SetImage(imgTileSet);
            }
            else if(!strcmp("layer", xml->getNodeName()))
            {
                if(!strcmp("Background", xml->getAttributeValue("name")))
                {
                    BGtData = xml->getAttributeValue("data");
                }
                else if(!strcmp("Foreground", xml->getAttributeValue("name")))
                {
                    FGtData = xml->getAttributeValue("data");
                }
            }
            break;
        }
    }
    // Delete XML parser object
    delete xml;
    // Done parsing!
    // ********************************
    // Load rectMap
    rectMap = new sf::IntRect[(imgTileSet.GetWidth() / TILE_SIZE) * (imgTileSet.GetHeight() / TILE_SIZE)];
    for(unsigned int ry = 0; ry < imgTileSet.GetHeight(); ry += TILE_SIZE)
    {
        for(unsigned int rx = 0; rx < imgTileSet.GetWidth(); rx += TILE_SIZE)
        {
            rectMap[(ry / TILE_SIZE) * (imgTileSet.GetHeight() / TILE_SIZE) + (rx / TILE_SIZE)] = sf::IntRect(rx, ry, TILE_SIZE, TILE_SIZE);
        }
    }
    // Load BGtMap
    BGtMap = new unsigned short[mapWidth * mapHeight];
    for(int ty = 0; ty < mapHeight; ty++)
    {
        for(int tx = 0; tx < mapWidth; tx++)
        {
            if(sf::Randomizer::Random(0.0f, 1.0f) <= 0.9f)
                BGtMap[ty * TILE_SIZE + tx] = 17;
            else
                BGtMap[ty * TILE_SIZE + tx] = 18;
        }
    }
    // Load FGtMap
    FGtMap = new unsigned short[mapWidth * mapHeight];
    for(int ty = 0; ty < mapHeight; ty++)
    {
        for(int tx = 0; tx < mapWidth; tx++)
        {
            if(sf::Randomizer::Random(0.0f, 1.0f) <= 0.1f)
                FGtMap[ty * TILE_SIZE + tx] = 19;
            else if(sf::Randomizer::Random(0.0f, 1.0f) <= 0.05f)
                FGtMap[ty * TILE_SIZE + tx] = 20;
            else
                FGtMap[ty * TILE_SIZE + tx] = 0;
        }
    }
    // Play BGM
    musBGM.Play();

    //std::cout << "BG data: *" << BGtData << "*\n";
    //std::cout << "FG data: *" << FGtData << "*\n";
    std::cout << "Map loaded in " << mapLoadTimer.GetElapsedTime() << " seconds!\n";
}

void Map::Update(const float& dt)
{
    // Constrain game view to map
    sf::Vector2f gameViewCenter = gViewP->GetCenter();
    float gViewHalfWidth = gViewP->GetSize().x / 2.0f;
    float gViewHalfHeight = gViewP->GetSize().y / 2.0f;
    // X left
    if(gameViewCenter.x < gViewHalfWidth)
        gViewP->SetCenter(gViewHalfWidth, gameViewCenter.y);
    // X right
    else if(gameViewCenter.x > mapWidth * TILE_SIZE - gViewHalfWidth)
        gViewP->SetCenter(mapWidth * TILE_SIZE - gViewHalfWidth, gameViewCenter.y);
    // Y top
    if(gameViewCenter.y < gViewHalfHeight)
        gViewP->SetCenter(gameViewCenter.x, gViewHalfHeight);
    // Y bottom
    else if(gameViewCenter.y > mapHeight * TILE_SIZE - gViewHalfHeight)
        gViewP->SetCenter(gameViewCenter.x, mapHeight * TILE_SIZE - gViewHalfHeight);
}

void Map::DrawLayer(unsigned short* layerTMap)
{
    sf::Vector2f gameViewCenter = appP->GetView().GetCenter();
    float tileRenderSpaceHalfWidth = appP->GetView().GetSize().x / 2.0f + TILE_SIZE;
    float tileRenderSpaceHalfHeight = appP->GetView().GetSize().y / 2.0f + TILE_SIZE;
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
                if(layerTMap[ty * TILE_SIZE + tx])
                {
                    sprTile.SetSubRect(rectMap[layerTMap[ty * TILE_SIZE + tx] - 1]);
                    sprTile.SetPosition(float(tx * TILE_SIZE), float(ty * TILE_SIZE));
                    appP->Draw(sprTile);
                }
            }
        }
    }
}

void Map::DrawBG()
{
    DrawLayer(BGtMap);
}

void Map::DrawFG()
{
    DrawLayer(FGtMap);
}

Map::~Map()
{
    delete[] FGtMap;
    delete[] BGtMap;
    delete[] rectMap;
}
