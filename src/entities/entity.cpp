#include "entity.hpp"
#include "../main.hpp"

Entity::Entity(Vector p, string path) : p(p)
{
	rectangle.x = p.x;
	rectangle.y = p.y;

	texture = Assets::get_texture(path, Main::get_renderer());
	SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h);

	rotation = 0.0;

	color = SDL_Color{};
	set_color(BLACK);
}

void Entity::draw(SDL_Renderer* renderer)
{
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
	SDL_RenderCopyEx(renderer, texture, NULL, &rectangle, rotation*180/M_PI, NULL, SDL_FLIP_NONE);
}

Vector& Entity::get()
{
	return p;
}

SDL_Rect& Entity::get_rect()
{
	return rectangle;
}

void Entity::set_color(int r, int g, int b)
{
	color.r = r;
	color.g = g;
	color.b = b;
}
