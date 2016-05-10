#include "brain.hpp"

Brain::Brain()
{
	int i = BRAIN_INPUT_LEN;
	int h = BRAIN_HIDDEN_LEN;
	int hl = BRAIN_HIDDEN_LAYER_LEN;
	int o = BRAIN_OUTPUT_LEN;

	Matrix new_matrix = Matrix(i+1,h);
	new_matrix.set_by_col(random_array(i*h+h));
	genes.push_back(new_matrix);

	for (int ii = 0; ii < hl-1; ii++)
	{
		new_matrix = Matrix(h+1,h);
		new_matrix.set_by_col(random_array(h*h+h));
		genes.push_back(new_matrix);
	}

	new_matrix = Matrix(h+1,o);
	new_matrix.set_by_col(random_array(o*h+o));
	genes.push_back(new_matrix);

	fitness = 0;
}

Matrix Brain::update(Matrix other_matrix)
{
	for (Matrix matrix : genes)
	{
		other_matrix = matrix.multiply(other_matrix);
		other_matrix.apply(Utils::sigmoid);
		other_matrix.add_bias();
	}
	return other_matrix;
}

void Brain::mutate()
{
	for (Matrix& matrix : genes)
	{
		struct Temp
		{
			static float random(float f) { 
				return (Utils::random_normalised() < MUTATION_CHANCE) ? f + (Utils::random_clamped() * MAX_PERTURB) : f; }
		};
		matrix.apply(Temp::random);
	}
}

void Brain::combine(Brain other_brain, int index)
{
	vector<Matrix> other_genes = other_brain.get_genes();
	if (genes.size() != other_genes.size()) throw runtime_error("Gene sizes does not match");

	int size = 0;
	bool already_cut = false;

	for (int location = 0; location < genes.size(); location++)
	{
		Matrix& matrix = genes[location];
		Matrix other_matrix = other_genes[location];

		size += matrix.get_width() * matrix.get_height();
		if (size >= index)
		{
			if (already_cut) genes[location] = other_matrix;
			else
			{
				int addition = 0;
				bool stop = false;
				for (int y = matrix.get_height()-1; y > 0 && !stop; y--)
				{
					for (int x = matrix.get_width()-1; x > 0 && !stop; x--)
					{
						addition++;
						if (addition >= (size-index)) 
						{
							stop = true;
							break;
						}

						matrix.set(x,y,other_matrix.get(x,y));
					}
				}
				already_cut = true;
			}
		}
	}
}

vector<Matrix>& Brain::get_genes()
{
	return genes;
}

int Brain::get_fitness()
{
	return fitness;
}

void Brain::set_fitness(int fitness)
{
	this->fitness = fitness;
}

void Brain::increase_fitness(int fitness)
{
	this->fitness += fitness;
}

vector<float> Brain::random_array(int length)
{
	vector<float> new_vector = vector<float>();
	for (int i = 0; i < length; i++)
	{
		new_vector.push_back(Utils::random_clamped());
	}
	return new_vector;	
}
