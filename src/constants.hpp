#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>
using namespace std;

const static int SCREEN_WIDTH = 640;
const static int SCREEN_HEIGHT = 480;

const static float FRAMERATE = 1000.0/60.0;

const static int ALIEN_WIDTH = 16;
const static int ALIEN_HEIGHT = 16;
const static int ALIEN_STARTING_X = 100;
const static int ALIEN_STARTING_Y = 20;
const static int ALIEN_SPACING = 12;
const static int ALIEN_SPEED = 15;
const static int MAX_ALIEN_BULLETS = 10;
extern int ALIEN_TICKS_TO_MOVE;

const static int CANNON_WIDTH = 16;
const static int CANNON_HEIGHT = 8;
const static int CANNON_SPEED = 1;
const static int CANNON_SPACER = 5;
const static int MAX_CANNON_SPEED = 1;
const static int MAX_CANNON_BULLETS = 3;

const static int BULLET_WIDTH = 2;
const static int BULLET_HEIGHT = 8;
const static int BULLET_SPEED = 2;

const static int CANNON_POPULATION = 30;
const static int ALIEN_POP_WIDTH = (SCREEN_WIDTH - 2 * ALIEN_STARTING_X) / (ALIEN_WIDTH + ALIEN_SPACING);
const static int ALIEN_POP_HEIGHT = 3;

extern bool TOURNAMENT;
extern bool COMBINE_TWO_POINT;

extern int ROLLING_AVERAGE;
extern int TOURNAMENT_SIZE;

extern float REWARD;
extern float PUNISHMENT;

const static int ELITES = 4;
//const static int EPOCH_TICK_OVER = 2000;
const static int HIT_DISTANCE = ALIEN_WIDTH/2; 

extern float MUTATION_CHANCE;
extern float COMBINE_CHANCE;
extern float MAX_PERTURB;

const static int BRAIN_INPUT_LEN = 7;
const static int BRAIN_OUTPUT_LEN = 2;
extern int BRAIN_HIDDEN_LEN;
const static int BRAIN_HIDDEN_LAYER_LEN = 1;

#define WHITE 255,255,255
#define BLACK 0,0,0

#define RED 255,0,0
#define BLUE 0,0,255
#define GREEN 0,255,0
#define PURPLE 255,0,255

#endif
