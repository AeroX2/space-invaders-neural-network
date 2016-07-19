#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <SDL2/SDL.h>

#include "constants.hpp"
#include "config.hpp"
#include "logic.hpp"

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool running = true;
bool fast = false;
Logic logic;

bool init();
void destroy();

#endif
