#pragma once
#include "BaseState.h"
#include "sfwdraw.h"
#include "SceneManager.h"

class Start : public BaseState
{
public: 
	int d;
	float timer;
	int select;

	virtual void init(int A_font)
	{
		d = A_font;
	}

	virtual void play()
	{
		timer = 4.f;
	}

	virtual void draw()
	{
		
		sfw::drawString(d, "Use [A] and [D] to rotate Bread Man", 300, 800, 32, 32, 0, 0, GREEN);
		sfw::drawString(d, "Use [F] to lure the murder biods", 300, 700, 32, 32, 0, 0, GREEN);
		sfw::drawString(d, "Press [SPACE] to stop Bread Man from spinning", 300, 600, 32, 32, 0, 0, GREEN);
		sfw::drawString(d, "Have the Boids eat everyone to win", 300, 500, 28, 28, 0, 0, GREEN);
		sfw::drawString(d, "Press [ENTER] to play", 300, 400, 32, 32, 0, 0, GREEN);
	}

	virtual void step() {};

	virtual size_t next() const
	{
		if (sfw::getKey(KEY_ENTER)) return (size_t) ENTER_PLAY;

		return OPTION;
	}
};
