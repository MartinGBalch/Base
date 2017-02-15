#pragma once

#include "base.h"
#include "Entity.h"
#include "PlayerController.h"

class GravityWell
{
	

public:
	float force = 20;
	bool isAlive = true;

	void attract(base::Transform *T, base::Transform *o_T, base::Rigidbody *o_rb)
	{
		base::vec2 f = (T->getGlobalPosition() - o_T->getGlobalPosition()).normal() * force;

		o_rb->addImpulse(f);

		if (shotRequest == true)
		{
			o_rb->drag *= 20;
		}
	}

};
