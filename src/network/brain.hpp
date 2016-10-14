#ifndef BRAIN_H
#define BRAIN_H

#include <vector>
#include <math.h>

#include "../constants.hpp"
#include "../utils.hpp"
#include "matrix.hpp"

class Brain
{
	public:
		Brain();
		Matrix update(Matrix other_matrix);

		void mutate();
		void combine_crossover(Brain other_brain, int index);
		void combine_two_point(Brain other_brain, int index1, int index2);

		vector<Matrix>& get_genes();
		float& get_fitness();
		void set_fitness(float fitness);

		vector<float> random_array(int length);
	private:
		vector<Matrix> genes;
		float fitness;
};

#endif


