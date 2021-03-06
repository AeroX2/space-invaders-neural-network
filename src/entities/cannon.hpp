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
		//Make constructor protected so we are sure nothing else is creating Cannon
		static Cannon* create(Vector p, Brain brain);
		virtual ~Cannon() {}
		virtual void update(Alien alien);
		virtual void draw(SDL_Renderer* renderer);
		void new_position();

		Vector& get();
		void set(Vector p);

		Brain& get_brain();
		void set_brain(Brain b);

		bool is_touched();
		
		bool is_best();
		void set_best(bool best);

		bool is_firing();
		void set_firing(bool firing);

		bool is_fired();
		void set_fired(bool fired);

		virtual float& get_fitness();
		virtual void set_fitness(float fitness);
	protected:
		Cannon(Vector p, Brain brain);
		bool touched;
		bool firing;
		bool fired;
		bool best;
		Vector v;
		Vector p;
		SDL_Rect rectangle;
		Brain brain;
};

#endif
