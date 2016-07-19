#ifndef CONSTANTS_H
#define CONSTANTS_H

const static int SCREEN_WIDTH = 640;
const static int SCREEN_HEIGHT = 480;

const static float FRAMERATE = 1000/60;

const static int ALIEN_WIDTH = 8;
const static int ALIEN_HEIGHT = 4;
const static int ALIEN_SPACING = 4;
const static int ALIEN_SPEED = 2;
const static int MAX_ALIEN_BULLETS = 10;

const static int CANNON_WIDTH = 8;
const static int CANNON_HEIGHT = 4;
const static int CANNON_SPEED = 1;
const static int CANNON_SPACER = 5;
const static int MAX_CANNON_SPEED = 5;
const static int MAX_CANNON_BULLETS = 3;

const static int BULLET_WIDTH = 2;
const static int BULLET_HEIGHT = 8;
const static int BULLET_SPEED = 2;

const static int CANNON_POPULATION = 30;
const static int ALIEN_POP_HEIGHT = 5;
const static int ALIEN_POP_WIDTH = 10;
const static int EPOCH_TICK_OVER = 2000;
const static int HIT_DISTANCE = ALIEN_WIDTH/2; 

static float MUTATION_CHANCE = 0.1;
static float COMBINE_CHANCE = 0.7;
static float MAX_PERTURB = 0.3;
static int ELITES = 4;

const static int BRAIN_INPUT_LEN = ALIEN_POP_WIDTH*ALIEN_POP_HEIGHT;
const static int BRAIN_OUTPUT_LEN = 2;
const static int BRAIN_HIDDEN_LEN = 6;
const static int BRAIN_HIDDEN_LAYER_LEN = 1;

#define WHITE 255,255,255
#define BLACK 0,0,0

#define RED 255,0,0
#define BLUE 0,255,0
#define GREEN 0,0,255
#define PURPLE 255,0,255

#endif
