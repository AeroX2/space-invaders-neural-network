#include "main.hpp"

//Windows MSYS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
int WinMain()
{
	Main::get_instance().run();
	return 0;
}
#else
int main()
{
	Main::get_instance().run();
	return 0;
}
#endif

Main::Main()
{
	window = NULL;
	renderer = NULL;
	font = NULL;

	running = true;
	fast = false;
	best = false;
}

void Main::run()
{
	if (init()) running = false;
	if (!running) cerr << "Error in initialising window\n";
	logic.init();

	double current_time, last_time, delta;
	current_time = SDL_GetTicks();
	while (running)
	{
		last_time = current_time;

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) running = false;
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_f)
				{
					cout << "F key pressed\n";
					Plotter::set_dirty();
					fast = !fast;
				}
				else if (e.key.keysym.sym == SDLK_b)
				{
					cout << "B key pressed\n";
					best = !best;
				}
			}
		}
		logic.update();

		if (fast)
		{
			if (Plotter::is_dirty())
			{
				SDL_SetRenderDrawColor(renderer,WHITE,0);
				SDL_RenderClear(renderer);

				Plotter::draw(renderer);

				SDL_RenderPresent(renderer);
			}
		}
		else
		{
			SDL_SetRenderDrawColor(renderer,WHITE,0);
			SDL_RenderClear(renderer);

			logic.draw(renderer);

			SDL_RenderPresent(renderer);

			current_time = SDL_GetTicks();
			delta = (current_time - last_time);
			if (delta < FRAMERATE) SDL_Delay(FRAMERATE - delta);
		}
	}

	destroy();
}

bool Main::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return true;
	window = SDL_CreateWindow("Neural Network Sweepers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) return true;
	renderer = SDL_CreateRenderer(window,0,SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) return true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	if (TTF_Init() < 0) return true;
	font = TTF_OpenFont("arial.ttf", 12);
	if (font == NULL) return true;

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) return true;

	if (Config::read_from_file("config.txt")) cout << "Using values from files\n";
	else cout << "Failed to read from file, using defaults\n";

	Plotter::init(10);
	Plotter::new_line(BLACK);
	Plotter::new_line(RED);

	return false;
}

void Main::destroy()
{
	Assets::destroy_textures();
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Main::draw_font_p(string message, int x, int y)
{
	SDL_Color color = {BLACK, 255};

	SDL_Surface* text_surface = TTF_RenderText_Blended(font, message.c_str(), color);
	if (text_surface == NULL)
	{
		cerr << "Couldn't create text to draw\n";
		return;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (texture == NULL)
	{
		 cerr << "Unable to create texture from rendered text\n";
		 return;
	}
	int width = 0;
	int height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	SDL_Rect offset = {x, y, width, height};

	SDL_RenderCopy(renderer, texture, NULL, &offset);

	SDL_FreeSurface(text_surface);
	SDL_DestroyTexture(texture);
}

Main& Main::get_instance()
{
	static Main main;
	return main;
}

void Main::draw_font(string message, int x, int y)
{
	get_instance().draw_font_p(message, x, y);
}

SDL_Renderer* Main::get_renderer()
{
	return get_instance().renderer;
}

bool Main::is_best()
{
	return get_instance().best;
}

