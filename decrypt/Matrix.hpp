#pragma once

#include <cassert>
#include <vector>

template<typename NumberType>
class Matrix
{
public:
	Matrix(int rows, int cols, const std::vector<std::vector<NumberType>>& init)
		: rows(rows), cols(cols), mat(init)
	{
	}

	Matrix(int rows, int cols)
		: rows(rows), cols(cols), mat(rows)
	{
		for(auto& row : mat)
		{
			row.resize(cols);
		}
	}

	NumberType Determinant()
	{
		assert(rows == cols);

		if(rows == 1)
		{
			return mat[0][0];
		}
		else if(rows == 2)
		{
			return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
		}

		NumberType sum = 0;
		Matrix minor(rows - 1, cols - 1);

		for(int c = 0; c < cols; c++)
		{
			Minor(minor, 0, c);
			sum += mat[0][c] * minor.Determinant() * ((c % 2) == 0 ? 1 : -1);
		}

		return sum;
	}

	Matrix Adjoint()
	{
		Matrix adjoint(rows, cols);
		Matrix minor(rows - 1, cols - 1);
		
		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < cols; c++)
			{
				Minor(minor, r, c);
				adjoint.mat[c][r] = minor.Determinant() * (((r + c) % 2) == 0 ? 1 : -1);
			}
		}

		return adjoint;
	}

	NumberType DeterminantFromAdjoint(const Matrix& adjoint)
	{
		assert(rows == cols);

		NumberType sum = 0;

		for(int c = 0; c < cols; c++)
		{
			sum += mat[0][c] * adjoint.mat[c][0];
		}

		return sum;
	}

	void Minor(Matrix& out, int rowExclude, int colExclude)
	{
		out.Resize(rows - 1, cols - 1);

		for(int r = 0, r1 = 0; r < rows; r++)
		{
			if(r == rowExclude)
				continue;

			for(int c = 0, c1 = 0; c < cols; c++)
			{
				if(c == colExclude)
					continue;

				out.mat[r1][c1] = mat[r][c];
				c1++;
			}

			r1++;
		}
	}

	std::vector<NumberType> MultiplyVector(const std::vector<NumberType>& v)
	{
		assert(cols == v.size());

		std::vector<NumberType> out(rows, 0);

		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < cols; c++)
			{
				out[r] += mat[r][c] * v[c];
			}
		}

		return out;
	}

	void MultiplyVector(std::vector<NumberType>& out, const std::vector<NumberType>& v)
	{
		assert(cols == v.size());

		out.resize(rows);

		for(int r = 0; r < rows; r++)
		{
			out[r] = 0;

			for(int c = 0; c < cols; c++)
			{
				out[r] += mat[r][c] * v[c];
			}
		}
	}

	void Resize(int newRows, int newCols)
	{
		if(rows == newRows && cols == newCols)
			return;

		rows = newRows;
		cols = newCols;

		mat.resize(newRows);

		for(auto& row : mat)
		{
			row.resize(newCols);
		}
	}

	std::vector<std::vector<NumberType>> mat;
	int rows, cols;
};