///////////////////////////////               MAIN.CPP                                                  /////////////////////////////////////
///////////////////////////////               COMMENTING COMPLETE BY PAUL...THANK YOU PAUL!             /////////////////////////////////////

// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "Menu.h"
#include "Credits.h"
#include "Player.h"
#include"Framework\GameState.h"

GameState gameState;
int main()
{
	//Create the window
	sf::RenderWindow window(sf::VideoMode(1200, 800), "jamies Game");

	// Initialise input and level objects.
	Input input;
	Level level(&window, &input, &gameState);
	Menu menu(&window, &input, &gameState);
	Credits credits(&window, &input, &gameState);

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	// Game Loop
	while (window.isOpen())
	{
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		//enum 
		switch (gameState.getCurrentState())
		{
		case (State::MENU):
			menu.handleInput(deltaTime);
			menu.update(deltaTime);
			menu.render();
			break;
		case(State::LEVEL):
			level.handleInput(deltaTime);
			level.update(deltaTime);
			level.render();
			break;
		case(State::PAUSE):
			level.handleInput(deltaTime);
			level.render();
			break;
		case(State::CREDITS):
			credits.handleInput(deltaTime);
			credits.update(deltaTime);
			credits.render();
			break;
		}


	}

}

