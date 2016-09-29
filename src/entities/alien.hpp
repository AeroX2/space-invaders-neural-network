#ifndef ALIEN_H
#define ALIEN_H

#include <SDL2/SDL.h>

#include "../constants.hpp"
#include "vector.hpp"

class Alien
{
	public:
		Alien(Vector p);
		void update();
		void draw(SDL_Renderer* renderer);
		void new_position();
		Vector& get();
		Vector& getv();
	private:
		Vector p;
		Vector v;
		SDL_Rect rectangle;
};

#endif
