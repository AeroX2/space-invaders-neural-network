#include "bullet.hpp"

Bullet::Bullet(Vector p, int id)
{
	this->p = p;
	this->id = id;

	rectangle.w = BULLET_WIDTH;
	rectangle.h = BULLET_HEIGHT;
	rectangle.x = p.x - rectangle.w / 2;
	rectangle.y = p.y;

	v.y = BULLET_SPEED;
}

void Bullet::update() 
{
	p.y -= v.y;	
	rectangle.y = round(p.y) - rectangle.h / 2;
}

void Bullet::draw(SDL_Renderer* renderer) 
{
	SDL_SetRenderDrawColor(renderer, RED, 255);
	SDL_RenderFillRect(renderer, &rectangle);
}

Vector& Bullet::get()
{
	return p;
}

int Bullet::get_id()
{
	return id;
}

SDL_Rect& Bullet::getbox()
{
	return rectangle;
}
