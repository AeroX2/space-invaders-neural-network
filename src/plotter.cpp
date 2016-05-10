#include "plotter.hpp"

vector<float> Plotter::points;
bool Plotter::dirty = true;
int Plotter::start_x = 0;
int Plotter::step_x = 0;
float Plotter::scale_x = 10;
float Plotter::scale_y = 30;

void Plotter::init(float start_x, float start_y, float step_x)
{
	Plotter::start_x = start_x;
	Plotter::step_x = step_x;
	add_point(start_y);
}

void Plotter::draw(SDL_Renderer* renderer)
{
	int x = 0;
	for (int point = 0; point < points.size()-1; point++)
	{
		SDL_SetRenderDrawColor(renderer, RED, 255);
		int point_1 = round(SCREEN_HEIGHT - points[point] * scale_y);
		int point_2 = round(SCREEN_HEIGHT - points[point+1] * scale_y);
		SDL_RenderDrawLine(renderer, x * scale_x, point_1, (x + step_x) * scale_x, point_2);
		x += step_x;
	}
	dirty = false;
}

void Plotter::add_point(float y)
{
	points.push_back(y);
	if (y * scale_y >= SCREEN_HEIGHT) scale_y /= 2;
	if (points.size() * step_x * scale_x >= SCREEN_WIDTH) scale_x /= 2;
	dirty = true;	
}

bool Plotter::is_dirty()
{
	return dirty;
}
