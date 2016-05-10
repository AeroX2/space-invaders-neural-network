#ifndef CONFIG_H
#define CONFIG_H

#include "constants.hpp"

using namespace std;

class Config
{
	public:
		static void read_from_file(char* filename));
};

#endif
