#include "controller.hpp"

int Controller::generation = 0;

bool Controller::compare_brains(Brain b1, Brain b2) { return b1.get_fitness() < b2.get_fitness(); }

vector<Brain> Controller::epoch(vector<Brain> population)
{
	//Sort pop
	sort(population.begin(), population.end(), Controller::compare_brains);

    //Average fitness
	float total_fitness = 0;
	float worst_fitness = population[0].get_fitness();
	float best_fitness = 0;
	for (Brain brain : population)
	{
		total_fitness += brain.get_fitness();
		best_fitness = fmax(best_fitness, brain.get_fitness());
		worst_fitness = fmin(worst_fitness, brain.get_fitness());
	}
	float average_fitness = total_fitness / population.size();

	Controller::generation += 1;
	cout << "Generation: " << Controller::generation << '\n';
	cout << "Total fitness: " << total_fitness << '\n';
	cout << "Average fitness: " << average_fitness << '\n';
	cout << "Max fitness: " << best_fitness << '\n';
	Plotter::add_point(0, average_fitness);
	Plotter::add_point(1, best_fitness);
	//if (CONTROL_SWEEPER) Plotter::add_point(2, control->get_fitness(), false);

	vector<Brain> new_population = vector<Brain>();

	//Elitism
	new_population.push_back(population[population.size()-1]);
	new_population.push_back(population[population.size()-2]);
	new_population.push_back(population[population.size()-3]);
	new_population.push_back(population[population.size()-4]);

	for (int i = 0; i < round((population.size()-4) / 2); i++)
	{
		Brain mum;
		Brain dad;
		if (TOURNAMENT)
		{
			mum = tournament(population);
			dad = tournament(population);
		}
		else
		{
			mum = roulette(population, total_fitness);
			dad = roulette(population, total_fitness);
		}

		if (Utils::random_normalised() < COMBINE_CHANCE)
		{
			int true_size = 0;
			for (Matrix matrix : mum.get_genes()) true_size += matrix.size();
			int combine_point_1 = Utils::random_range_int(0, true_size-1);
			int combine_point_2 = Utils::random_range_int(0, true_size-1);

			if (Utils::random_normalised() < COMBINE_CHANCE)
			{
				Brain temp_brain = mum;

				int min_point = min(combine_point_1, combine_point_2);
				int max_point = max(combine_point_1, combine_point_2);

				if (COMBINE_TWO_POINT)
				{
					mum.combine_two_point(dad, min_point, max_point);
					dad.combine_two_point(temp_brain, min_point, max_point);
				}
				else
				{
					mum.combine_crossover(dad, combine_point_1);
					dad.combine_crossover(temp_brain, combine_point_1);
				}
			}
		}

		mum.mutate();
		dad.mutate();

		new_population.push_back(mum);
		new_population.push_back(dad);
	}
	return new_population;
}

Brain& Controller::roulette(vector<Brain> population, int total_fitness)
{
	float rand_fitness = Utils::random_range_int(0, total_fitness);

	int sum_fitness = 0;
	for (Brain& brain : population)
	{
		sum_fitness += brain.get_fitness();
		if (sum_fitness >= rand_fitness) return brain;
	}
	throw runtime_error("Couldn't find suitable brain with fitness");
}

Brain& Controller::tournament(vector<Brain> population)
{
	int random = Utils::random_range_int(0, population.size()-1);
	Brain& best = population[random];

	for (int i = 0; i < TOURNAMENT_SIZE; i++)
	{
		random = Utils::random_range_int(0, population.size()-1);
		if (population[random].get_fitness() > best.get_fitness()) best = population[random];
	}
	return best;
}
