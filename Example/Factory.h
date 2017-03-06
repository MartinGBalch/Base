#pragma once

#include "Entity.h"

class Factory
{	
	ObjectPool<Entity>	  entities;
	
	// The factory will store an object pool for each component type
	ObjectPool<Transform> transforms;
	ObjectPool<Rigidbody> rigidbodies;
	ObjectPool<Collider>  colliders;
	ObjectPool<Sprite>    sprites;
	ObjectPool<Lifetime>  lifetimes;
	ObjectPool<Camera>    cameras;
	ObjectPool<Text>	  texts;
	ObjectPool<PlayerController> controllers;
	ObjectPool<GravityWell> gravwells;
	ObjectPool<Target> target;
	ObjectPool<GameTimer> time;

public:

	// iterators to access the entity pool
	ObjectPool<Entity>::iterator begin() { return entities.begin(); }
	ObjectPool<Entity>::iterator end() { return entities.end(); }

	// for now, they're all the same size
	Factory(size_t size = 512)
		: entities(size), transforms(size), rigidbodies(size),
		colliders(size), sprites(size), lifetimes(size),
		cameras(size), controllers(size), texts(size), gravwells(size), target(size), time(size)
	{
	}

	// What follows are specialized spawning functions
	// just observe the steps taken and replicate for your own usages

	ObjectPool<Entity>::iterator spawnCamera(float w2, float h2, float zoom)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->camera = cameras.push();
		e->camera->offset = vec2{w2,h2};
		e->camera->scale = vec2{ zoom,zoom };
		return e;
	}

	ObjectPool<Entity>::iterator spawnStaticImage(unsigned sprite, float x, float y, float w, float h)
	{
		auto e = entities.push();
		e->transform = transforms.push();
		e->sprite = sprites.push();
		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{1920,1080};
		e->transform->setLocalPosition(vec2{ 560,225 });	
		return e;
	}

	ObjectPool<Entity>::iterator spawnBullet(unsigned sprite, vec2 pos, vec2 dim, float ang, float impulse, unsigned faction)
	{
		
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->lifetime = lifetimes.push();
		//e->collider = colliders.push();
		e->gravwell = gravwells.push();
		

		e->transform->setLocalPosition(pos);
		e->transform->setLocalScale(dim);
		e->transform->setLocalAngle(ang);

		e->sprite->sprite_id = sprite;
		e->sprite->dimensions = vec2{1.2f, 1.2f};

		e->rigidbody->addImpulse(e->transform->getGlobalUp() * 300);

		e->lifetime->lifespan = 5.f;

		
		
		return e;
	}

	ObjectPool<Entity>::iterator spawnPlayer(unsigned sprite, unsigned font)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		e->controller = controllers.push();
		e->text = texts.push();
		e->rigidbody->drag = 1;

		e->text->sprite_id = font;
		e->text->offset = vec2{ -24,-24 };
		e->text->off_scale = vec2{.5f,.5f};
		//e->text->setString("Player1");

		e->transform->setLocalScale(vec2{130,140});

		e->transform->setGlobalPosition(vec2{ 540, -264 });

		e->sprite->sprite_id = sprite;

		return e;
	}

	ObjectPool<Entity>::iterator spawnAsteroid(unsigned sprite)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		e->rigidbody = rigidbodies.push();
		e->sprite = sprites.push();
		e->collider = colliders.push();
		

		e->transform->setLocalScale(vec2{ 48,48 });
		e->rigidbody->drag = 1;

		e->transform->setGlobalPosition(vec2{randRange(2000, 2000), -500});



		/*e->rigidbody->addSpin(rand01()*12-6);*/

		e->sprite->sprite_id = sprite;

		return e;
	}

	ObjectPool<Entity>::iterator spawnTarget(unsigned sprite, float x, float y)
	{
		auto e = entities.push();

		e->transform = transforms.push();
		/*e->rigidbody = rigidbodies.push();*/
		e->sprite = sprites.push();
		e->collider = colliders.push(Collider(.5f));
		e->target = target.push();
		
		e->transform->setLocalScale(vec2{ 148,148 });
		e->transform->setGlobalPosition(vec2{x,y});

		


		/*e->rigidbody->addSpin(rand01()*12-6);*/

		e->sprite->sprite_id = sprite;

		return e;
	}
};


