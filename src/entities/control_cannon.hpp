#ifndef CONTROL_SWEEPER_H
#define CONTROL_SWEEPER_H

#include "cannon.hpp"

class Control_Cannon : public Cannon
{
	public:
		Control_Cannon(Vector p, Brain brain);
		virtual void update(Vector mine_location);
		virtual void draw(SDL_Renderer* renderer);
};

#endif
