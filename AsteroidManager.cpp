///////////////////////////////               ASTEROIDMANAGER.CPP                   /////////////////////////////////////
///////////////////////////////               COMMENTING NOT COMPLETE               /////////////////////////////////////

//single include
#include "AsteroidManager.h"

//constructor creating all the asteroids in the vector and loading the asteroid texture and sound effect for being destroyed
AsteroidManager::AsteroidManager()
{
	texture.loadFromFile("gfx/asteroid.png");
	audioManager.addSound("sfx/explosion.wav", "explosion");

	for (int i = 0; i < 40; i++)
	{
		asteroids.push_back(Asteroid());
		asteroids[i].setAlive(false);
		asteroids[i].setTexture(&texture);
		asteroids[i].setSize(sf::Vector2f(40, 35));
		asteroids[i].setCollisionBox(3, 3, 38, 33);

	}
}

//empty
AsteroidManager::~AsteroidManager(){}

//Function:  collision detection between Asteroids/Walls, Asteroids/Asteroids, Asteroids/Player, Asteroids/Bullets
//Parameter: Deltatime and a reference to Player class to incriment the score
//output:    None
void AsteroidManager::update(float dt, Player &player)
{
	//assigning two new vectors to the elements of the vectors used in BulletManager and WallManager
	std::vector<Wall> walls1 = wallManager->getWalls1();
	std::vector<Bullet>* bullet1 = bulletManager->getBullets();

// first collision check for asteroids vs player. If collision detected then destroy the asteroid and reduce player score by 50
for (auto& astroid : asteroids)
	{
		if (Collision::checkBoundingBox(&astroid, &player))
		{
			if (astroid.isAlive())
			{
				astroid.setAlive(false);
				astroid.setPosition(-200, -200);
				astroid.setVelocity(0, 0);
				player.setScore(-50);
			}
		}
	}

//second collision check for asteroids vs bullets. If collision detected then destroy bullet and asteroid,play sound effect and increase player score by 50
//first for loop goes through the bullet vector
for (auto& bullet : *bullet1)
{
	//second for loop goes through the asteroid vector
	for (auto& astroid : asteroids)
	{
		//using the premade function by Paul..good job Paul!
		if (Collision::checkBoundingBox(&astroid, &bullet))
		{
			// only do this if statment is the asteroid is set to alive. 
			if (astroid.isAlive())
			{
				audioManager.playSoundbyName("explosion");
				bullet.setAlive(false);
				astroid.setAlive(false);
				astroid.setPosition(-100, 0);
				player.setScore(50);
			}
		}
	}
}

//third collision check for asteroids vs walls. This needed  to be more complex due to the possibility of hitting all 4 sides of collision box
for (auto& wall : walls1)
{
	for (auto& astroid : asteroids)
	{
		if (Collision::checkBoundingBox(&astroid, &wall))
		{
			// First you calculate the middle of both object x and Y
			asteroidICentre.x = astroid.getPosition().x + (astroid.getSize().x * 0.5);
			asteroidICentre.y = astroid.getPosition().y + (astroid.getSize().y * 0.5);
			wallCentre.x = wall.getPosition().x + (wall.getSize().x * 0.5);
			wallCentre.y = wall.getPosition().y + (wall.getSize().y * 0.5);

			//two ints to work out which direction has been hit
			float tempX, tempY;
			
			
			tempX = abs(wallCentre.x - asteroidICentre.x);
			tempY = abs(wallCentre.y - asteroidICentre.y);

			if (tempX < 0)
			{
				tempX *= -1;
			}

			if (tempY < 0)
			{
				tempY *= -1;
			}

			//if the center of X of both objects are closer than the Ys of both objects then collision is horizontal
			if (tempX > tempY)
			{
				// if the walls x is great than the asteroids x then that means its colliding with the left of the wall
				if (wallCentre.x > asteroidICentre.x)
				{
					astroid.setVelocity(astroid.getVelocity().x * (-1), astroid.getVelocity().y);
				}
				// if the walls x is less than the asteroids x then that means its colliding with the right of the wall
				if (wallCentre.x < asteroidICentre.x)
				{
					astroid.setVelocity(astroid.getVelocity().x * (-1), astroid.getVelocity().y);
				}
			}
			//if the center of Y of both objects are closer than the Xs of both objects then collision is vertical
			else
			{
				// if the walls y is great than the asteroids y then that means its colliding with the top of the wall
				if (wallCentre.y > asteroidICentre.y)
				{
					astroid.setVelocity(astroid.getVelocity().x , astroid.getVelocity().y * (-1));
				}
				// if the walls y is less than the asteroids y then that means its colliding with the bottom of the wall
				else
				{
					astroid.setVelocity(astroid.getVelocity().x, astroid.getVelocity().y * (-1));
				}
			}
		}
	}
}

//fourth collision check for asteroids vs asteroids. Left as the simple for loop we learned to show both variations
//inside collision is same as above so will not comment to reduce lines
for (int i = 0; i < asteroids.size(); i++)
{
	for (int j = 0; j < asteroids.size(); j++)
	{
		if (i != j)
		{
			if (asteroids[i].isAlive())
			{
				if (Collision::checkBoundingBox(&asteroids[i], &asteroids[j]))
				{
					asteroidICentre.x = asteroids[i].getPosition().x + (asteroids[i].getSize().x * 0.5);
					asteroidICentre.y = asteroids[i].getPosition().y + (asteroids[i].getSize().y * 0.5);
					asteroidJCentre.x = asteroids[j].getPosition().x + (asteroids[j].getSize().x * 0.5);
					asteroidJCentre.y = asteroids[j].getPosition().y + (asteroids[j].getSize().y * 0.5);

					float tempX, tempY;

					tempX = abs(asteroidJCentre.x - asteroidICentre.x);
					tempY = abs(asteroidJCentre.y - asteroidICentre.y);

					if (tempX < 0)
					{
						tempX *= -1;
					}

					if (tempY < 0)
					{
						tempY *= -1;
					}

					if (tempX > tempY)
					{
						//left side
						if (asteroidJCentre.x > asteroidICentre.x)
						{
							asteroids[i].setVelocity(asteroids[i].getVelocity().x * (-1), asteroids[i].getVelocity().y);
							asteroids[j].setVelocity(asteroids[j].getVelocity().x * (-1), asteroids[j].getVelocity().y);
						}
						//right
						if (asteroidJCentre.x < asteroidICentre.x)
						{
							asteroids[i].setVelocity(asteroids[i].getVelocity().x * (-1), asteroids[i].getVelocity().y);
							asteroids[j].setVelocity(asteroids[j].getVelocity().x * (-1), asteroids[j].getVelocity().y);
						}
					}
					else
					{
						if (asteroidJCentre.y > asteroidICentre.y)
						{
							asteroids[i].setVelocity(asteroids[i].getVelocity().x, asteroids[i].getVelocity().y * (-1));
							asteroids[j].setVelocity(asteroids[j].getVelocity().x, asteroids[j].getVelocity().y * (-1));
						}
						else
						{
							asteroids[i].setVelocity(asteroids[i].getVelocity().x, asteroids[i].getVelocity().y * (-1));
							asteroids[j].setVelocity(asteroids[j].getVelocity().x, asteroids[j].getVelocity().y * (-1));
						}
					}
				}
				asteroids[i].update(dt);
			}
		}
	}
 }


//spawn new ball
//find a dead ball, make alive, move to spawn point, give random velocity
void AsteroidManager::spawn()
{
	asteroids[0].setPosition(1860, 220);
	asteroids[1].setPosition(1860, 280);
	asteroids[2].setPosition(1860, 350);
	asteroids[3].setPosition(1860, 410);
	asteroids[4].setPosition(1860, 550);
	asteroids[5].setPosition(1940, 250);
	asteroids[6].setPosition(1940, 310);
	asteroids[7].setPosition(1940, 380);
	asteroids[8].setPosition(1940, 410);
	asteroids[9].setPosition(1940, 590);
	asteroids[10].setPosition(2020, 220);
	asteroids[11].setPosition(2020, 280);
	asteroids[12].setPosition(2020, 350);
	asteroids[13].setPosition(2020, 410);
	asteroids[14].setPosition(2020, 550);
	asteroids[15].setPosition(2100, 250);
	asteroids[16].setPosition(2100, 310);
	asteroids[17].setPosition(2100, 380);
	asteroids[18].setPosition(2100, 410);
	asteroids[19].setPosition(2100, 590);
	asteroids[20].setPosition(2180, 220);
	asteroids[21].setPosition(2180, 280);
	asteroids[22].setPosition(2180, 350);
	asteroids[23].setPosition(2180, 410);
	asteroids[24].setPosition(2180, 550);
	asteroids[25].setPosition(2260, 250);
	asteroids[26].setPosition(2260, 310);
	asteroids[27].setPosition(2260, 380);
	asteroids[28].setPosition(2260, 410);
	asteroids[29].setPosition(2260, 590);
	asteroids[30].setPosition(2340, 220);
	asteroids[31].setPosition(2340, 280);
	asteroids[32].setPosition(2340, 350);
	asteroids[33].setPosition(2340, 410);
	asteroids[34].setPosition(2340, 550);
	asteroids[35].setPosition(2420, 250);
	asteroids[36].setPosition(2420, 310);
	asteroids[37].setPosition(2420, 380);
	asteroids[38].setPosition(2420, 410);
	asteroids[39].setPosition(2420, 590);

	for (int i = 0; i < asteroids.size(); i++)
	{
		if (!asteroids[i].isAlive())
		{
			asteroids[i].setAlive(true);
			asteroids[i].setVelocity(1, 1);
			
			return;
		}
	}

}

//Render all alive asteroids
void AsteroidManager::render(sf::RenderWindow* window)
{
	for (int i = 0; i < asteroids.size(); i++)
	{
		if (asteroids[i].isAlive())
		{
			window->draw(asteroids[i]);
		}
	}
}
