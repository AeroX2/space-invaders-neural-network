#include "controller.hpp"

int Controller::generation = 0;

bool Controller::compare_brains(Brain b1, Brain b2) { return b1.get_fitness() < b2.get_fitness(); }

vector<Brain> Controller::epoch(vector<Brain> population)
{
	//Sort pop
	sort(population.begin(),population.end(),Controller::compare_brains);

    //Average fitness
	int total_fitness = 0;
	int best_fitness = 0;
	for (Brain brain : population)
	{
		total_fitness += brain.get_fitness(); 
		best_fitness = max(best_fitness, brain.get_fitness());
	}
	float average_fitness = ((float)total_fitness / (float)population.size());

	Controller::generation += 1;
	cout << "Generation: " << Controller::generation << endl;
	cout << "Total fitness: " << total_fitness << endl;
	cout << "Average fitness: " << average_fitness << endl;
	cout << "Max fitness: " << best_fitness << endl;
	Plotter::add_point(average_fitness);

	vector<Brain> new_population = vector<Brain>();

	//Elitism
	for (int i = 1; i <= ELITES; i++)
		new_population.push_back(population[population.size()-i]);

	for (int i = 0; i < round((population.size()-ELITES) / 2); i++)
	{
		Brain mum = roulette(population,total_fitness);
		Brain dad = roulette(population,total_fitness);
		
		if (Utils::random_normalised() < COMBINE_CHANCE)
		{
			int true_size = 0;
			for (Matrix matrix : mum.get_genes()) true_size += matrix.get_matrix().size();
			int combine_point = rand() % (true_size-1);

			if (Utils::random_normalised() < COMBINE_CHANCE)
			{
				Brain temp_brain = mum;
				mum.combine(dad, combine_point);
				dad.combine(temp_brain, combine_point);
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
	float rand_fitness = Utils::random_range(0,total_fitness); 

	int sum_fitness = 0;
	for (Brain& brain : population)
	{
		sum_fitness += brain.get_fitness();
		if (sum_fitness >= rand_fitness) return brain;
	}
	throw runtime_error("Couldn't find suitable brain with fitness");
}

