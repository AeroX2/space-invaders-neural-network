#ifndef BRAIN_H
#define BRAIN_H

#include <vector>

#include "../constants.hpp"
#include "../utils.hpp"
#include "matrix.hpp"

class Brain
{
	public:
		Brain();
		Matrix update(Matrix other_matrix);

		void mutate();
		void combine(Brain other_brain, int index);

		vector<Matrix>& get_genes();
		int get_fitness();
		void set_fitness(int fitness);
		void increase_fitness(int fitness);

		vector<float> random_array(int length);
	private:
		vector<Matrix> genes;
		int fitness;
};

#endif


