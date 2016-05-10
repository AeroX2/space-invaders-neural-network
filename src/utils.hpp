#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdlib.h> 
#include <iostream>

using namespace std;

class Utils
{
	public:
		static float random_range(float min, float max);
		static float random_normalised();
		static float random_clamped();

		static float sigmoid(float num);
};

#endif
