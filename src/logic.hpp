#ifndef LOGIC_H
#define LOGIC_H

#include <memory>
#include <functional>

#include "entities/alien.hpp"
#include "entities/cannon.hpp"
#include "network/brain.hpp"
#include "network/matrix.hpp"

#include "controller.hpp"

struct SDL_Renderer;

using namespace std;

class Logic
{
	public:
		Logic();
		void update();
		void draw(SDL_Renderer* renderer);
	private:
		void reset_aliens();
		vector<reference_wrapper<Cannon>> cannons;
		vector<Alien> aliens;
		vector<Bullet> bullets;

		int ticks;
		int max_fitness;
		size_t current_player;
};

#endif
