#include "control_cannon.hpp"

Control_Cannon::Control_Cannon(Vector p, Brain brain) : Cannon(p, brain)
{
	this->p = p;

	rectangle.w = 10;
	rectangle.h = 10;
}

void Control_Cannon::update(Vector mine_location) 
{
}

void Control_Cannon::draw(SDL_Renderer* renderer) 
{
}
