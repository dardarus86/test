///////////////////////////////               CREDITS.CPP                   /////////////////////////////////////
///////////////////////////////               COMMENTING NOT COMPLETE               /////////////////////////////////////

#include "Credits.h"

Credits::Credits(sf::RenderWindow* hwnd, Input* in, GameState *state)
{

	window = hwnd;
	input = in;
	gameState = state;



	// render text
	if (!font.loadFromFile("font/galactic.ttf"))
	{
		std::cout << "Error loading font/n";
	}
	backgroundtexture.loadFromFile("gfx/credit.png");

	backgroundobj.setTexture(&backgroundtexture);
	backgroundobj.setPosition(0, 0);
	backgroundobj.setSize(sf::Vector2f(1200, 800));

	background.addFrame(sf::IntRect(0, 0, 500, 333));
	background.addFrame(sf::IntRect(500, 0, 500, 333));
	background.addFrame(sf::IntRect(1000, 0, 500, 333));
	background.addFrame(sf::IntRect(1500, 0, 500, 333));
	background.addFrame(sf::IntRect(2000, 0, 500, 333));
	background.addFrame(sf::IntRect(2500, 0, 500, 333));
	background.addFrame(sf::IntRect(3000, 0, 500, 333));
	background.addFrame(sf::IntRect(3500, 0, 500, 333));
	background.addFrame(sf::IntRect(4000, 0, 500, 333));
	background.addFrame(sf::IntRect(4500, 0, 500, 333));
	background.addFrame(sf::IntRect(5000, 0, 500, 333));
	background.addFrame(sf::IntRect(5500, 0, 500, 333));
	background.addFrame(sf::IntRect(6000, 0, 500, 333));
	background.setFrameSpeed(0.1f);

	background.getCurrentFrame();

	text.setFont(font);
	
	text.setCharacterSize(44);
	text.setFillColor(sf::Color::Red);
	text.setPosition(350, 50);

	text2.setFont(font);
	text2.setString("Please maximize then return size to fix the screen issue. Game should really be called 'BUGADIUS' ");
	text2.setCharacterSize(16);
	text2.setPosition(10, 20);


}


Credits::~Credits()
{

}




void Credits::playerScore(Player & player)
{
	finalScore = player.getScore();
}

// Update game objects
void Credits::update(float dt )
{
	text.setString("Thank you for playing\n Your Final score was: " + finalScore);
	backgroundobj.setTextureRect(background.getCurrentFrame());
	background.animate(dt);


}

// Render level
void Credits::render()
{
	beginDraw();
	window->draw(backgroundobj);
	window->draw(text);
	window->draw(text2);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Credits::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Credits::endDraw()
{
	window->display();
}