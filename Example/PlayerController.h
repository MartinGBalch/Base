#pragma once

#include "Base.h"


class PlayerController
{

public:
	float turnSpeed = .3f, stopPower = 10;
	float shotTimer = 0.0f;
	
	bool shotRequest = false;

	void poll(base::Transform *T, base::Rigidbody *rb, float dt)
	{
		

		if (sfw::getKey('A'))
			rb->addTorque(turnSpeed);

		if (sfw::getKey('D'))
			rb->addTorque(-turnSpeed);
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