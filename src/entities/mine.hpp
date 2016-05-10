#ifndef MINE_H
#define MINE_H

#include <SDL2/SDL.h>

#include "../constants.hpp"
#include "vector.hpp"

class Mine
{
	public:
		Mine();
		void draw(SDL_Renderer* renderer);
		void new_position();
		Vector& get();
	private:
		Vector p;
		SDL_Rect rectangle;
};

#endif
