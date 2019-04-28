///////////////////////////////               ASTEROID.H                        /////////////////////////////////////
///////////////////////////////               COMMENTING COMPLETE               /////////////////////////////////////
#pragma once
#include "Framework/GameObject.h"


//class to control a single asteroid
class Asteroid : public GameObject
{
public:
	//empty constructor/deconstructor
	Asteroid();
	~Asteroid();
	//function for the movement of asteroid
	void update(float dt);

};
