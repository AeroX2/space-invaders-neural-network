#include "utils.hpp"

float Utils::random_range(float min, float max)
{
	return min+(rand())/((RAND_MAX/(max-min)));
}

float Utils::random_normalised()
{
	return random_range(0,1);
}

float Utils::random_clamped()
{
	return random_range(-1,1);
}

float Utils::sigmoid(float num)
{
	//return num/(1+fabs(num));
	return 1/(1+exp(-num));
}
