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

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Perf.hpp"
#include "Map.hpp"

class Game
{
public:
    Game(int appWidth = 800, int appHeight = 600);
    void Run();
    ~Game();

private:
    sf::RenderWindow app;
    sf::Event event;
    float dt;
    sf::View gView;
    sf::View uiView;

    // * Temporary audio testing *
    sf::SoundBuffer bufBlip;
    sf::Sound sndBlip;

    // Performance stats
    Perf* perf;
    // Current map
    Map* gMap;

    // Main loop functions
    void Update(const float& dt);
    void Draw();
};

#endif
