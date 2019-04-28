///////////////////////////////               ASTEROID.CPP                   /////////////////////////////////////
///////////////////////////////               COMMENTING COMPLETE            /////////////////////////////////////

//single include
#include "Asteroid.h"

// constructor/deconstructor empty
Asteroid::Asteroid(){}
Asteroid::~Asteroid(){}

//Function:  Used to move the object and check to see if asteroids are hitting top or bottom of screen
//Parameter: Deltatime
//output:    None
void Asteroid::update(float dt)
{
	move(velocity*dt);


	if (getPosition().y <= 100 || getPosition().y >= 650)
	{
		velocity.y = -velocity.y;
	}

}
