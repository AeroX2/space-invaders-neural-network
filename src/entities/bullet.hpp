#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

#include "../constants.hpp"
#include "vector.hpp"
#include "../network/brain.hpp"

class Vector;

class Bullet
{
	public:
		Bullet(Vector p, int id);
		virtual ~Bullet() {}
		virtual void update();
		virtual void draw(SDL_Renderer* renderer);
		Vector& get();
		int get_id();
		SDL_Rect& getbox();
	protected:
		int id;
		Vector v;
		Vector p;
		SDL_Rect rectangle;
};

#endif
