#pragma once
#include "base.h"
#include <cstring>
#include <stdio.h>
using namespace base;

class GameTimer
{
public:
	void update(Text &timer, float dt)
	{
		char buffer[80];
		sprintf_s(buffer, "Time letf: %d", dt);
		timer.setString(buffer);

	}
};
