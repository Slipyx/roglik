/*
 * roglik - Perf.cpp
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

#include "Perf.hpp"
#include <sstream>

Perf::Perf(sf::RenderWindow& app)
{
    appP = &app;
    font.LoadFromFile("fonts/DroidSans-Bold.ttf"); // TODO: Get from font manager
    txtFps.SetFont(font);
    txtFps.SetString(sf::String("0 FPS"));
    txtFps.SetCharacterSize(12);
    txtFps.SetPosition(appP->GetWidth() - txtFps.GetRect().Width - 8, 4.0f); // Align 8 pixels from right of window
    txtFps.SetColor(sf::Color(255, 0, 0));
    // Reset fps timer when constructor is finished
    fpsUdateTimer.Reset();
}

void Perf::Update(const float& dt)
{
    float fps = 1.0f / dt;
    if(fpsUdateTimer.GetElapsedTime() >= 1.0f)
    {
        // Update fps string
        std::stringstream ssfps;
        ssfps << (int)fps << " FPS";
        txtFps.SetString(sf::String(ssfps.str()));
        txtFps.SetPosition(appP->GetWidth() - txtFps.GetRect().Width - 8, 4.0f); // Re-align
        // Change color based on fps range
        if(fps >= 40)
            txtFps.SetColor(sf::Color(0, 255, 0));
        else if(fps >= 20)
            txtFps.SetColor(sf::Color(255, 255, 0));
        else
            txtFps.SetColor(sf::Color(255, 0, 0));
        fpsUdateTimer.Reset();
    }
}

void Perf::Draw()
{
    appP->Draw(txtFps);
}

Perf::~Perf()
{
}
