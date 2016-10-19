#ifndef LOGIC_H
#define LOGIC_H

#include <memory>

//Windows MSYS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <string>
	#include <sstream>
	template<typename T> std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
#endif

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
		~Logic();
		void init();
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
