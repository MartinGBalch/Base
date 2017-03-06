#pragma once
#include "sfwdraw.h"
#include "BaseState.h"

#pragma once
#include "BaseState.h"
#include "sfwdraw.h"
#include "SceneManager.h"

class Win : public BaseState
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
		sfw::drawString(d, "You killed them all...Congrats", 650, 600, 32, 32, 0, 0, RED);
	}

	virtual void step() { timer -= sfw::getDeltaTime(); };

	virtual size_t next() const
	{
		if (timer <= 0) return (size_t)ENTER_OPTION;

		return WIN;
	}
};

