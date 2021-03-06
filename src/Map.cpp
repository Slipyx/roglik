/*
 * Copyright (c) 2011 Josh Koch
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
            if(BGtData.at(0) == '\n')
                BGtData.erase(0, 1);
            BGtMap[ty * TILE_SIZE + tx] = atoi(BGtData.substr(0, BGtData.find(',')).c_str());
            BGtData.erase(0, BGtData.find(',') + 1);
        }
    }
    // Load FGtMap
    FGtMap = new unsigned short[mapWidth * mapHeight];
    for(int ty = 0; ty < mapHeight; ty++)
    {
        for(int tx = 0; tx < mapWidth; tx++)
        {
            if(FGtData.at(0) == '\n')
                FGtData.erase(0, 1);
            FGtMap[ty * TILE_SIZE + tx] = atoi(FGtData.substr(0, FGtData.find(',')).c_str());
            FGtData.erase(0, FGtData.find(',') + 1);
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
