#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

//Windows MSYS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <stdexcept>
#endif

#include "../utils.hpp"

using namespace std;

class Matrix
{
	public:
		Matrix(int width, int height);
		void set(int x, int y, float value);
		float get(int x, int y);
		void set_by_row(vector<float> other_matrix);
		void set_by_col(vector<float> other_matrix);
		void zero_fill();
		void add_bias();

		Matrix add(Matrix other_matrix);
		Matrix multiply(Matrix other_matrix);

		void apply(float (*func)(float));
		void print();

		int get_width();
		int get_height();
		int size();
		vector<vector<float>> get_matrix();
	private:
		int width,height;
		vector<vector<float>> matrix;
};

#endif
