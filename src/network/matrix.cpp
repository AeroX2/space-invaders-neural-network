#include "matrix.hpp"

Matrix::Matrix(int width, int height)
{
	this->width = width;
	this->height = height;
	zero_fill();
}

void Matrix::set(int x, int y, float value)
{
	matrix.at(y).at(x) = value;
}

float Matrix::get(int x, int y)
{
	return matrix.at(y).at(x);
}

void Matrix::set_by_row(vector<float> other_matrix)
{
	for (int y = 0; y < get_height(); y++)
	{
		for (int x = 0; x < get_width(); x++)
		{
			set(x,y,other_matrix[y*get_width()+x]);
		}
	}	
}

void Matrix::set_by_col(vector<float> other_matrix)
{
	for (int y = 0; y < get_height(); y++)
	{
		for (int x = 0; x < get_width(); x++)
		{
			set(x,y,other_matrix[x*get_height()+y]);
		}
	}	
}

void Matrix::zero_fill()
{
	matrix = vector<vector<float>>(height, vector<float>(width));
}

void Matrix::add_bias()
{
	height++;
	matrix.push_back(vector<float>());	
	matrix[matrix.size()-1].push_back(-1);
}

Matrix Matrix::add(Matrix other_matrix)
{
	return Matrix(0,0);
}

Matrix Matrix::multiply(Matrix other_matrix)
{
	if (get_width() != other_matrix.get_height()) throw runtime_error("Matrix sizes are not compatiable to multiply");

	Matrix new_matrix = Matrix(other_matrix.get_width(), get_height());
	for (int y0 = 0; y0 < new_matrix.get_height(); y0++)
	{
		for (int x0 = 0; x0 < new_matrix.get_width(); x0++)
		{
			float addition = 0;
			for (int y1 = 0; y1 < other_matrix.get_height(); y1++)
			{
				addition += get(y1, y0) * other_matrix.get(x0, y1);
			}
			new_matrix.set(x0, y0, addition);
		}
	}
	return new_matrix;
}

void Matrix::apply(float(*func)(float))
{
	for (int y = 0; y < get_height(); y++)
	{
		for (int x = 0; x < get_width(); x++)
		{
			set(x,y,func(get(x,y)));
		}
	}
}

void Matrix::print()
{
	for (int i = 0; i < matrix.size(); i++)
	{
		cout << "[ ";
		for (int ii = 0; ii < matrix[i].size(); ii++)
		{
			cout << matrix[i][ii] << " ";
		}
		cout << "]" << endl;
	}
	cout << endl;
}

int Matrix::get_width()
{
	return width;
}

int Matrix::get_height()
{
	return height;
}

vector<vector<float>> Matrix::get_matrix()
{
	return matrix;
}