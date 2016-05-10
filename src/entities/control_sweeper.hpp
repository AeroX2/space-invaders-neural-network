#ifndef CONTROL_SWEEPER_H
#define CONTROL_SWEEPER_H

#include "sweeper.hpp"

class Control_Sweeper : public Sweeper
{
	public:
		static Control_Sweeper* create(Vector p, Brain brain);
		void update(Vector mine_location) override;
		void draw(SDL_Renderer* renderer) override;
	private:
		Control_Sweeper(Vector p, Brain brain);
};

#endif
