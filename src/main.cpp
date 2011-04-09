/*
 * roglik - main.cpp
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

#include "Game.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    int sw = 854, sh = 480;
    // Check command line options
    for(int i = 1; i < argc; i++)
    {
        // --noscale: Run game in 1:1 graphics scale - 427x240 resolution
        if(!strcmp("--noscale", argv[i]))
        {
            std::cout << "Setting 1:1 scale...\n";
            sw = 427;
            sh = 240;
        }
    }

    // Initialize core game object and load initial map
    Game game(sw, sh);

    // Start running main game loop
    game.Run();

    return 0;
}
