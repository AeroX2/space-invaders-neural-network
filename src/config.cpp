#include "config.hpp"

bool Config::read_from_file(string filename)
{
	ifstream file(filename);
	if (!file) return false;

	char param_description[40];
	file >> MUTATION_CHANCE;  
	file >> param_description;  
	file >> COMBINE_CHANCE;  
	file >> param_description;  
	file >> MAX_PERTURB;  
	file >> param_description; 

	cout << MUTATION_CHANCE << " " << COMBINE_CHANCE << " " << MAX_PERTURB << endl;

	return true;
}
