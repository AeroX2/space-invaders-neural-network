#ifndef CONFIG_H
#define CONFIG_H

#include <fstream>
#include <iostream>
#include "constants.hpp"

using namespace std;

class Config
{
	public:
		static bool read_from_file(string filename);
};

#endif
