#ifndef LOGIC_H
#define LOGIC_H

#include <memory>
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
		vector<Bullet> bullets;
		vector<Alien> aliens;
		int ticks;
		int max_fitness;
};

#endif
