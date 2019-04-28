///////////////////////////////               ASTEROIDMANAGER.H                 /////////////////////////////////////
///////////////////////////////               COMMENTING COMPLETE               /////////////////////////////////////

#pragma once
//.h includes
#include "Asteroid.h"
#include "Framework/Collision.h"
#include "Framework/AudioManager.h"
#include "WallManager.h"
#include "BulletManager.h"
#include "WallManager.h"
#include "Player.h"
#include <SFML/Audio.hpp>
// library includes
#include <vector>


//This class is used for spawning, controlling collisions and modifying the bullet/players scores slightly
class AsteroidManager
{
public:
	//default constructor/deconstrctor
	AsteroidManager();
	~AsteroidManager();

	// used to spawn asteroids at on creation of level.
	void spawn();
	//collision checks, movement assigned at beginning of level, deletion of bullets on colision, adding player score on collision
	void update(float dt, Player &player);
	// drawing the asteroids to the screen in level.cpp
	void render(sf::RenderWindow* window);

	// function to get access to the WallManager class
	void setWallManager(WallManager* wm)
	{
		wallManager = wm;
	}

	// function to get access to the BulletManager class
	void setBulletManager(BulletManager* bm)
	{
		this->bulletManager = bm;
	}


private:
	//vector of  asteroid objects from Asteroid class
	std::vector<Asteroid> asteroids;
	//texture used for the asteroid sprite
	sf::Texture texture;

	//object pointers used in the set functions above
	WallManager* wallManager;
	BulletManager* bulletManager;
	//AudioManager object being used for the explosion sound effect
	AudioManager audioManager;
	//Vectors used in the collision calculation
	sf::Vector2f asteroidICentre;
	sf::Vector2f asteroidJCentre;
	sf::Vector2f wallCentre;
};
