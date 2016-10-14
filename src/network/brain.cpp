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
	struct Temp
	{
		static float check(float f)
		{
			//TODO Can f be less than 0?
			//cout << f << '\n';
			//fabs(f+1) because of -1 bias
			if ((f < -1 || f > 1) && fabs(f+1) > 0.001) throw runtime_error("Input matrix is not normalised");
			return f;
		}
	};
	other_matrix.apply(Temp::check);
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
			static float random(float f) { return (Utils::random_normalised() < MUTATION_CHANCE) ?
				                                   f + (Utils::random_clamped() * MAX_PERTURB) : f; }
		};
		matrix.apply(Temp::random);
	}
}

void Brain::combine_crossover(Brain other_brain, int index)
{
	vector<Matrix> other_genes = other_brain.get_genes();
	if (genes.size() != other_genes.size()) throw runtime_error("Gene sizes does not match");

	int size = 0;
	bool already_cut = false;

	for (size_t location = 0; location < genes.size(); location++)
	{
		Matrix& matrix = genes[location];
		Matrix other_matrix = other_genes[location];

		size += matrix.size();
		if (size >= index)
		{
			if (already_cut) genes[location] = other_matrix;
			else
			{
				for (int y = matrix.get_height()-1; y > 0; y--)
				{
					for (int x = matrix.get_width()-1; x > 0; x--)
					{
						if (y*matrix.get_width()+x >= size-index) break;
						matrix.set(x,y,other_matrix.get(x,y));
					}
				}
				already_cut = true;
			}
		}
	}
}

void Brain::combine_two_point(Brain other_brain, int index1, int index2)
{
	vector<Matrix> other_genes = other_brain.get_genes();
	if (genes.size() != other_genes.size()) throw runtime_error("Gene sizes does not match");

	int size = 0;
	bool first_cut = false;
	bool second_cut = false;

	for (size_t location = 0; location < genes.size(); location++)
	{
		Matrix& matrix = genes[location];
		Matrix other_matrix = other_genes[location];

		size += matrix.size();
		if (size > index1 && !first_cut)
		{
			index1 -= size - matrix.size();
			index1 = floor((float) index1 / matrix.get_width());

			int temp_index2 = index2 - (size - matrix.size());
			temp_index2 = min(temp_index2, size-1);
			temp_index2 = floor((float) temp_index2 / matrix.get_width());

			for (int y = index1; y <= temp_index2; y++)
			{
				for (int x = 0; x < matrix.get_width(); x++)
				{
					matrix.set(x,y,other_matrix.get(x,y));
				}
			}
			first_cut = true;
		}
		else if (first_cut)
		{
			//Not sure if < or <=
			if (size < index2) genes[location] = other_matrix;
			else if (!second_cut)
			{
				index2 -= size - matrix.size();
				index2 = floor((float) index2 / matrix.get_width());
				for (int y = 0; y <= index2; y++)
				{
					for (int x = 0; x < matrix.get_width()-1; x++)
					{
						matrix.set(x,y,other_matrix.get(x,y));
					}
				}
				second_cut = true;
			}
		}
	}
}

vector<Matrix>& Brain::get_genes()
{
	return genes;
}

float& Brain::get_fitness()
{
	return fitness;
}

void Brain::set_fitness(float fitness)
{
	this->fitness = fitness;
}

vector<float> Brain::random_array(int length)
{
	vector<float> new_vector = vector<float>();
	for (int i = 0; i < length; i++)
	{
		//new_vector.push_back(i);
		new_vector.push_back(Utils::random_clamped());
	}
	return new_vector;
}
