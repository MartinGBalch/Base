#pragma once
#include <iostream>
#include "Base.h"

using namespace std;

float shotTimer = 0.0f;
bool shotRequest = false;
class PlayerController
{

public:
	float turnSpeed = .3f, stopPower = 10;
	bool shotRequest = false;
	int hp = 6;
	
	

	void poll(base::Transform *T, base::Rigidbody *rb, float dt)
	{
		

		if (sfw::getKey('A'))
		{
			rb->addTorque(turnSpeed);
			rb->drag += .5f;
		}

			if (sfw::getKey('D'))
			{
				rb->addTorque(-turnSpeed);
				rb->drag += .5f;
			}
		if (sfw::getKey(' '))
			rb->addTorque(rb->angularVelocity * -stopPower);

		
	
			

		shotTimer -= dt;
		if (sfw::getKey('F') && shotTimer < 0)
		{
			shotRequest = true;
			shotTimer = 5.f;
		}
		else shotRequest = false;
	}

};