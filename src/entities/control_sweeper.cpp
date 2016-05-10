#include "control_sweeper.hpp"

Control_Sweeper::Control_Sweeper(Vector p, Brain brain) : Sweeper(p, brain)
{
	this->p = p;

	rectangle.x = p.x;
	rectangle.y = p.y;
	rectangle.w = 10;
	rectangle.h = 10;

	rotation = 0.0;
	speed = CONTROL_SWEEPER_SPEED;
}

void Control_Sweeper::update(Vector mine_location) 
{
	Vector temp = mine_location - p;
	rotation = atan2(temp.y, temp.x);

	v.x = cos(rotation) * speed;
	v.y = sin(rotation) * speed;

	if (v.x > MAX_SWEEPER_SPEED) v.x = MAX_SWEEPER_SPEED; 
	else if (v.x < -MAX_SWEEPER_SPEED) v.x = -MAX_SWEEPER_SPEED; 
	if (v.y > MAX_SWEEPER_SPEED) v.y = MAX_SWEEPER_SPEED; 
	else if (v.y < -MAX_SWEEPER_SPEED) v.y = -MAX_SWEEPER_SPEED; 

	p += v;
	rectangle.x = round(p.x);
	rectangle.y = round(p.y);

	get_brain().set_fitness(0);
}

void Control_Sweeper::draw(SDL_Renderer* renderer) 
{
	SDL_SetRenderDrawColor(renderer, PURPLE, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

Control_Sweeper* Control_Sweeper::create(Vector p, Brain brain)
{
	return new Control_Sweeper(p, brain);
}
