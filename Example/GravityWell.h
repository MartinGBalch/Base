#pragma once

#include "base.h"
#include "Entity.h"
#include "PlayerController.h"

class GravityWell
{
	

public:
	float force = 300;
	bool isAlive = true;

	void attract(base::Transform *T, base::Transform *o_T, base::Rigidbody *o_rb, PlayerController *PC)
	{
		base::vec2 f = (T->getGlobalPosition() - o_T->getGlobalPosition()).normal() * force;

		o_rb->addForce(f);

		if (PC->shotTimer <= 0)
		{
			o_rb->drag = 500;
		}
	}

};
