#pragma once
#include "base.h"
#include <cstring>
#include <stdio.h>
#include "sfwdraw.h"
#include "SceneManager.h"
using namespace base;

class GameTimer
{
public:
	float time = 20.f;
	int Trgt = 6;
	void update(Text &timer, float dt)
	{
		char buffer[80];
		//sprintf_s(buffer, "Time letf: %d", dt);
		timer.setString(buffer);

		time -= sfw::getDeltaTime();

	}

	
};
