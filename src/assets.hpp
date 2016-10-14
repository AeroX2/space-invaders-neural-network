#ifndef ASSETS_H
#define ASSETS_H

#include <iostream>
#include <unordered_map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class Assets
{
	public:
		static SDL_Texture* get_texture(string path, SDL_Renderer* renderer);
		static void destroy_textures();
	private:
		static unordered_map<string, SDL_Texture*> images;
};

#endif
