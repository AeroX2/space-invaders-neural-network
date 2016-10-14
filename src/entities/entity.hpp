#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

//Windows MSYS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <stdexcept>
#endif

#include "../network/brain.hpp"
#include "../constants.hpp"
#include "../assets.hpp"
#include "vector.hpp"

class Entity
{
	public:
		Entity(Vector p, string path);
		virtual ~Entity() {};
		virtual void draw(SDL_Renderer* renderer);

		Vector& get();
		SDL_Rect& get_rect();

		void set_color(int r, int g, int b);
	protected:
		double rotation;

		Vector v;
		Vector p;
		SDL_Rect rectangle;
		SDL_Color color;
		SDL_Texture* texture;
};

#endif
