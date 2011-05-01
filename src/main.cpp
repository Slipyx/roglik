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

#include "Game.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    int sw = 640, sh = 480;
    // Check command line options
    for(int i = 1; i < argc; i++)
    {
        // --noscale: Run game in 1:1 graphics scale - 320x240 resolution
        if(!strcmp("--noscale", argv[i]))
        {
            std::cout << "Setting 1:1 scale...\n";
            sw = 320;
            sh = 240;
        }
    }

    // Initialize core game object and load initial map
    Game game(sw, sh);

    // Start running main game loop
    game.Run();

    return 0;
}
