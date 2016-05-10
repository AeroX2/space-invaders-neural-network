#ifndef CONSTANTS_H
#define CONSTANTS_H

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const float FRAMERATE = 1000/60;

const int POPULATION = 20;
const int MINE_LEN = 40;
const int EPOCH_TICK_OVER = 2000;
const int HIT_DISTANCE = 5;

const float MUTATION_CHANCE = 0.1;
const float COMBINE_CHANCE = 0.7;
const float MAX_PERTURB = 0.3;

const float CONTROL_SWEEPER_SPEED = 1.5;
const float MAX_SWEEPER_TURN_RATE = 0.3;
const float MAX_SWEEPER_SPEED = 2.0;

const int BRAIN_INPUT_LEN = 4;
const int BRAIN_OUTPUT_LEN = 2;
const int BRAIN_HIDDEN_LEN = 6;
const int BRAIN_HIDDEN_LAYER_LEN = 1;

#define WHITE 255,255,255
#define BLACK 0,0,0
#define RED 255,0,0
#define PURPLE 255,0,255

#endif
