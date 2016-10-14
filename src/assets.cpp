#include "assets.hpp"

unordered_map<string, SDL_Texture*> Assets::images;

SDL_Texture* Assets::get_texture(string path, SDL_Renderer* renderer)
{
	if (images.count(path)) return images[path];

	SDL_Texture* new_texture = NULL;
    SDL_Surface* loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL) 
	{
		cerr << "Could not load texture\n";
		return NULL;
	}
    else
    {
        new_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (new_texture == NULL)
        {
            cerr << "Unable to create texture: " << path << " SDL Error: " << SDL_GetError();
			return NULL;
        }

        SDL_FreeSurface(loaded_surface);
    }
	images[path] = new_texture;
	return new_texture;
}

void Assets::destroy_textures()
{
	for (auto value : images) SDL_DestroyTexture(value.second);
}
