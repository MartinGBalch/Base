#pragma once
#include <iostream>
#include "sfwdraw.h"
#include "Base.h"

using namespace base;

class Target 
{
public:
	int hp = 45000;
	
	bool isAlive = true;
	unsigned healthy, damaged, dead;

	


	void update(Sprite *sp, unsigned SmileyFace)
	{
		if (hp < 22500)
		{
			sp->sprite_id = SmileyFace;
		}
		
	}


	void eatten(Transform *T, Transform *b_T, Rigidbody *b_rb) {}
};