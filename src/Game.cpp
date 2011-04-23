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

#include "Game.hpp"
#include <iostream>

// ****************************************************************************
// Initialize core Game members and load starting map
Game::Game(int appWidth, int appHeight)
{
    app.Create(sf::VideoMode(appWidth, appHeight, 32), "roglik", sf::Style::Close);
    app.SetFramerateLimit(60);
    app.EnableVerticalSync(true);
    app.EnableKeyRepeat(false);
    //gView = app.GetDefaultView();
    gView.SetSize(320, 240);
    gView.SetCenter(160, 120);
    // UI view
    uiView = gView;
    // Performace stats
    perf = new Perf(app, uiView);

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

    while(app.PollEvent(event))
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
    perf->Update(dt);
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
    perf->Draw();

    app.Display();
}

// ****************************************************************************
// Cleanup core game objects
Game::~Game()
{
    delete gMap;
    delete perf;
}
