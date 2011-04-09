/*
 * roglik - Game.cpp
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

// ****************************************************************************
// Initialize core Game members and load starting map
Game::Game(int appWidth, int appHeight) : perf(app, uiView)
{
    app.Create(sf::VideoMode(appWidth, appHeight, 32), "roglik", sf::Style::Close);
    app.SetFramerateLimit(60);
    app.EnableVerticalSync(true);
    app.EnableKeyRepeat(false);
    //gView = app.GetDefaultView();
    gView.SetSize(427, 240);
    gView.SetCenter(213.5f, 120);
    // UI view
    uiView.SetSize(427, 240);
    uiView.SetCenter(213.5f, 120);

    // Loadup initial map
    gMap = new Map(app, gView, "rogGrass.xml");
    bufBlip.LoadFromFile("sndfx/blip.wav");
    sndBlip.SetBuffer(bufBlip);
}

// ****************************************************************************
// Start main loop
void Game::Run()
{
    while(app.IsOpened())
    {
        dt = app.GetFrameTime();

        Update(dt);
        Draw();
    }
}

// ****************************************************************************
// Update logic and input
void Game::Update(const float& dt)
{
    const sf::Input& input = app.GetInput();
    // Input
    if(input.IsKeyDown(sf::Key::Right))
        gView.Move(120.0f * dt, 0.0f);
    else if(input.IsKeyDown(sf::Key::Left))
        gView.Move(-120.0f * dt, 0.0f);
    if(input.IsKeyDown(sf::Key::Up))
        gView.Move(0.0f, -120.0f * dt);
    else if(input.IsKeyDown(sf::Key::Down))
        gView.Move(0.0f, 120.0f * dt);

    while(app.GetEvent(event))
    {
        if(event.Type == sf::Event::Closed)
            app.Close();
        if(event.Type == sf::Event::KeyPressed)
        {
            // Fire keypressed callbacks
            if(event.Key.Code == sf::Key::Q)
                app.Close();
            else if(event.Key.Code == sf::Key::A)
            {
                std::cout << sf::Randomizer::Random(0.0f, 1.0f) << '\n';
                sndBlip.Play();
            }
        }
    }

    // Logic
    gMap->Update(dt);
    perf.Update(dt);
}

// ****************************************************************************
// Clear screen and draw to display
void Game::Draw()
{
    //app.Clear(sf::Color(255, 127, 0)); // Don't need clear when drawing over whole window

    // Render
    app.SetView(gView);

    gMap->DrawBG();
    gMap->DrawFG();

    app.SetView(uiView);
    perf.Draw();

    app.Display();
}

// ****************************************************************************
// Cleanup core game objects
Game::~Game()
{
    delete gMap;
}
