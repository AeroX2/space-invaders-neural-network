#include "mine.hpp"

Mine::Mine()
{
	new_position();

	rectangle.x = p.x;
	rectangle.y = p.y;
	rectangle.w = 5;
	rectangle.h = 5;
}

void Mine::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, BLACK, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

void Mine::new_position()
{
	int rand_x = rand() % SCREEN_WIDTH;
	int rand_y = rand() % SCREEN_HEIGHT;
	this->p = Vector(rand_x, rand_y);

	this->rectangle.x = p.x;
	this->rectangle.y = p.y;
}

Vector& Mine::get()
{
	return p;
}

