
#include "sfwdraw.h"
#include "GameState.h"
#include "SceneManager.h"
#include "Start.h"
#include "Win.h"


/*
	The main function should be used for application state management.
	Currently, only one state is implemented here, you'll need to add additional
	and get them to behave properly.
*/
void main()
{
	float SCREEN_WIDTH =1900, SCREEN_HEIGHT = 1000;
	sfw::initContext(SCREEN_WIDTH, SCREEN_HEIGHT);

	unsigned spr_font = sfw::loadTextureMap("../res/fontmap.png", 16, 16);
	Start option;
	Win win;

	GameState gs;

	option.init(spr_font);
	win.init(spr_font);

	APP_STATE state = ENTER_OPTION;


	gs.init(); // called once

	gs.play(); // Should be called each time the state is transitioned into

	

	while (sfw::stepContext())
	{
		
		switch (state)
		{
		case ENTER_OPTION:
			option.play();
		case OPTION:
			option.step();
			option.draw();
			state = (APP_STATE)option.next();
			break;
		case ENTER_WIN:
			win.play();
		case WIN:
			win.step();
			win.draw();
			state = (APP_STATE)win.next();
			break;
		case ENTER_PLAY:
			gs.play();
		case PLAY:
			gs.step();
			gs.draw();
			state = (APP_STATE)gs.next();

		}


		//gs.next(); Determine the ID of the next state to transition to.
	}

	gs.stop(); // should be called each time the state is transitioned out of

	gs.term(); // called once


	sfw::termContext();

}