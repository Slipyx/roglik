/*
 * roglik - Perf.h
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

#ifndef PERF_H
#define PERF_H

#include <SFML/Graphics.hpp>

class Perf
{
public:
    Perf(sf::RenderWindow& app);
    void Update(const float& dt);
    void Draw();
    ~Perf();

private:
    // app pointer for drawing with
    sf::RenderWindow* appP;
    // FPS display
    sf::Font font;
    sf::Text txtFps;
    sf::Clock fpsUdateTimer;
};

#endif
