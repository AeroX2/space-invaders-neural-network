#include "config.hpp"

bool Config::read_from_file(string filename)
{
	ifstream file(filename);
	if (!file) return false;

	char param_description[25];
	file >> ROLLING_AVERAGE;
	file >> param_description;
	file >> TOURNAMENT;
	file >> param_description;
	file >> COMBINE_TWO_POINT;
	file >> param_description;
	file >> CONTROL_SWEEPER;
	file >> param_description;
	file >> POPULATION;
	file >> param_description;
	file >> MINE_LEN;
	file >> param_description;
	file >> EPOCH_TICK_OVER;
	file >> param_description;
	file >> HIT_DISTANCE;
	file >> param_description;
	file >> TOURNAMENT_SIZE;
	file >> param_description;
	file >> REWARD;
	file >> param_description;
	file >> PUNISHMENT;
	file >> param_description;
	file >> MUTATION_CHANCE;
	file >> param_description;
	file >> COMBINE_CHANCE;
	file >> param_description;
	file >> MAX_PERTURB;
	file >> param_description;
	file >> MAX_SWEEPER_TURN_RATE;
	file >> param_description;
	file >> BRAIN_HIDDEN_LEN;
	file >> param_description;

	cout << "Rolling average: " << ROLLING_AVERAGE << '\n';
	cout << "Tournament selection: " << TOURNAMENT << '\n';
	cout << "Control sweeper: " << CONTROL_SWEEPER << '\n';
	cout << "Combine by two points: " << COMBINE_TWO_POINT << '\n';
	cout << "Population: " << POPULATION << '\n';
	cout << "Reward: " << REWARD << '\n';
	cout << "Punishment: " << PUNISHMENT << '\n';
	cout << "Mine len: " << MINE_LEN << '\n';
	cout << "Epoch tick over: " << EPOCH_TICK_OVER << '\n';
	cout << "Hit distance: " << HIT_DISTANCE << '\n';
	cout << "Tournament size: " << TOURNAMENT_SIZE << '\n';
	cout << "Mutation chance: " << MUTATION_CHANCE << '\n';
	cout << "Combine chance: " << COMBINE_CHANCE << '\n';
	cout << "Max perturb: " << MAX_PERTURB << '\n';
	cout << "Max sweeper turn rate: " << MAX_SWEEPER_TURN_RATE << '\n';
	cout << "Brain hidden len: " << BRAIN_HIDDEN_LEN << '\n';

	return true;
}
