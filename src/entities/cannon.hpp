#ifndef CANNON_H
#define CANNON_H

#include <SDL2/SDL.h>

#include "../constants.hpp"
#include "../network/brain.hpp"
#include "vector.hpp"
#include "alien.hpp"
#include "bullet.hpp"

class Vector;

class Cannon
{
	public:
		Cannon(Vector p, Brain brain);
		virtual void update(vector<Alien> &aliens);
		virtual void draw(SDL_Renderer* renderer);
		void new_position();

		Vector& get();
		void set(Vector p);

		Brain& get_brain();
		void set_brain(Brain b);

		bool is_best();
		void set_best(bool best);

		bool is_firing();
	protected:
		bool firing;
		bool best;
		Vector v;
		Vector p;
		SDL_Rect rectangle;
		Brain brain;
};

#endif
