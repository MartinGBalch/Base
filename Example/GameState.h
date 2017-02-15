#pragma once

#include "sfwdraw.h"
#include "BaseState.h"
#include "Factory.h"



/*
	The gamestate represents a discrete container of all that is 
	necessary to drive the game experience.

	A factory object is used to manage the creation and deletion of
	objects in the simulation.

	The game state updates the entities within the factory using
	a series of 'systems.'
*/

class GameState : public BaseState
{
	Factory factory;
	unsigned spr_space, spr_ship, spr_bullet, spr_roid, spr_font;
	ObjectPool<Entity>::iterator currentCamera;

public:
	virtual void init()
	{
		spr_bullet = sfw::loadTextureMap("../res/garlic.png");
		spr_space = sfw::loadTextureMap("../res/park.jpg");
		spr_ship = sfw::loadTextureMap("../res/bman.gif");
		spr_roid = sfw::loadTextureMap("../res/boid.png");
		spr_font = sfw::loadTextureMap("../res/font.png",32,4);
	}

	virtual void play()
	{
		// delete any old entities sitting around
		for (auto it = factory.begin(); it != factory.end(); it->onFree(), it.free());

		// setup a default camera
		currentCamera = factory.spawnCamera(800, 600, 1);
		currentCamera->transform->setGlobalPosition(vec2{ 400, 300 });

		// call some spawning functions!
		factory.spawnStaticImage(spr_space, 0, 0, 800, 600);

		factory.spawnPlayer(spr_ship, spr_font);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		factory.spawnAsteroid(spr_roid);
		
	}

	virtual void stop()
	{

	}

	// should return what state we're going to.
	// REMEMBER TO HAVE ENTRY AND STAY states for each application state!
	virtual size_t next() const { return 0; }


	// update loop, where 'systems' exist
	virtual void step()
	{
		float dt = sfw::getDeltaTime();

		// maybe spawn some asteroids here.

		for(auto it = factory.begin(); it != factory.end();) // no++!
		{
			bool del = false; // does this entity end up dying?
			auto &e = *it;    // convenience reference

			// rigidbody update
			if (e.transform && e.rigidbody)
				e.rigidbody->integrate(&e.transform, dt);

			// controller update
			if (e.transform && e.rigidbody && e.controller)
			{
				e.controller->poll(&e.transform, &e.rigidbody, dt);
				if (e.controller->shotRequest) // controller requested a bullet fire
				{
					factory.spawnBullet(spr_bullet, e.transform->getGlobalPosition()  + e.transform->getGlobalUp()*48,
											vec2{ 32,32 }, e.transform->getGlobalAngle(), 200, 1);
				}
			}
			// lifetime decay update
			if (e.lifetime)
			{
				e.lifetime->age(dt);
				if (!e.lifetime->isAlive())
					del = true;
			}


			if (e.gravwell && e.transform)
			{
				for (auto bit = factory.begin(); bit != factory.end(); bit++)
					if(it != bit && bit->rigidbody && bit->transform && !bit->controller)
					{
						e.gravwell->attract(&e.transform, &bit->transform, &bit->rigidbody);
					}
			}

			// ++ here, because free increments in case of deletions
			if (!del) it++;
			else
			{
				it->onFree();
				it.free();
			}
		}


		
		for(auto it = factory.begin(); it != factory.end(); it++) // for each entity
			for(auto bit = it; bit != factory.end(); bit++)		  // for every other entity
				if (it != bit && it->transform && it->collider && bit->transform && bit->collider)
				// if they aren't the same and they both have collidable bits...
				{
					// test their bounding boxes
					if (base::BoundsTest(&it->transform, &it->collider, &bit->transform, &bit->collider))
					{
						// if true, get the penetration and normal from the convex hulls
						auto cd = base::ColliderTest(&it->transform, &it->collider, &bit->transform, &bit->collider);
						
						// if there was a collision,
						if (cd.result())
						{							
							// condition for dynamic resolution
							/*else*/ if (it->rigidbody && bit->rigidbody && !bit->controller && !it->controller)
								base::DynamicResolution(cd,&it->transform,&it->rigidbody, &bit->transform, &bit->rigidbody);
							
							//else if (bit->rigidbody && it->rigidbody && !it->controller)
							//	base::DynamicResolution(cd, &bit->transform, &bit->rigidbody, &it->transform, &it->rigidbody);


							else if (it->rigidbody && bit->controller)
								base::StaticResolution(cd, &it->transform, &it->rigidbody);
							else if (it->controller && bit->rigidbody)
								base::StaticResolution(cd, &bit->transform, &bit->rigidbody);
							// condition for static resolution
							else if (it->rigidbody && !bit->rigidbody)							
								base::StaticResolution(cd, &it->transform, &it->rigidbody);			

							
						}
					}
				}

	}


	virtual void draw()	
	{
		// kind of round about, but this is the camera matrix from the factory's current camera
		auto cam = currentCamera->camera->getCameraMatrix(&currentCamera->transform);

		// draw sprites
		for each(auto &e in factory)
			if (e.transform && e.sprite)
				e.sprite->draw(&e.transform, cam);

		// draw text
		for each(auto &e in factory)
			if (e.transform && e.text)
				e.text->draw(&e.transform, cam);


//#ifdef _DEBUG
//		for each(auto &e in factory)
//			if (e.transform)
//				e.transform->draw(cam);
//
//		for each(auto &e in factory)
//			if (e.transform && e.collider)
//				e.collider->draw(&e.transform, cam);
//
//		for each(auto &e in factory)
//			if (e.transform && e.rigidbody)
//				e.rigidbody->draw(&e.transform, cam);
//#endif
	}
};