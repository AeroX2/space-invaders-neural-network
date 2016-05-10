#ifndef PLOTTER_H
#define PLOTTER_H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "constants.hpp"

using namespace std;

class Plotter
{
	static vector<float> points;

	public:
		static void init(float start_x, float start_y, float step_x);
		static void draw(SDL_Renderer* renderer);

		static void add_point(float y);
		static void resize(float blub);
		static bool is_dirty();
	private:
		static bool dirty;
		static int start_x;
		static int step_x;
		static float scale_x;
		static float scale_y;
};

#endif
