#ifndef LOGIC_H
#define LOGIC_H

#include <memory>
#include <functional>

#include "entities/alien.hpp"
#include "entities/cannon.hpp"
#include "entities/control_cannon.hpp"
#include "network/brain.hpp"
#include "network/matrix.hpp"

#include "controller.hpp"

class SDL_Renderer;

using namespace std;

class Logic
{
	public:
		Logic();
		void update(double delta);
		void draw(SDL_Renderer* renderer);
	private:
		vector<reference_wrapper<Cannon>> cannons;
		vector<Alien> aliens;
		vector<Bullet> bullets;
		int ticks;
		int max_fitness;
};

#endif
