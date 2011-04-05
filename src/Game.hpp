/*
 * roglik - Game.hpp
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

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Perf.hpp"

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

    // * Temporary background placement *
    sf::Image imgPlanetBG;
    sf::Sprite sprPlanetBG;
    // * Temporary audio testing *
    sf::Music musAmbMain;
    sf::SoundBuffer bufBlip;
    sf::Sound sndBlip;

    // Performance stats
    Perf perf;

    // Main loop functions
    void Update(const float& dt);
    void Draw();
};

#endif
