#include "alien.hpp"

Alien::Alien(Vector p)
{
	this->p = p;

	rectangle.x = p.x;
	rectangle.y = p.y;
	rectangle.w = ALIEN_WIDTH;
	rectangle.h = ALIEN_HEIGHT;

	v.x = ALIEN_SPEED;
}

void Alien::update()
{
	p.x += v.x;	

	rectangle.x = round(p.x);
	rectangle.y = round(p.y);
}

void Alien::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, WHITE, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

Vector& Alien::get()
{
	return p;
}

