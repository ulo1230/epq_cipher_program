#pragma once

#include <cmath>
#include <string>
#include <stdexcept>

class Playfair
{
public:
	std::string Encode(const std::string& plaintext, const std::string& grid)
	{
		int gridSize = std::sqrt(grid.size());
		std::string ciphertext(plaintext.length() - (plaintext.length() % 2), ' ');

		for(size_t i = 0; i < ciphertext.length(); i += 2)
		{
			int c1_row = -1, c1_col = -1;
			int c2_row = -1, c2_col = -1;

			for(size_t j = 0; j < grid.length(); j++)
			{
				if(grid[j] == plaintext[i])
				{
					c1_row = j / gridSize;
					c1_col = j % gridSize;
				}

				if(grid[j] == plaintext[i + 1])
				{
					c2_row = j / gridSize;
					c2_col = j % gridSize;
				}

				if(c1_row != -1 && c2_row != -1)
					break;
			}

			if(c1_row == -1 || c1_row == -1)
				throw std::out_of_range("invalid character in plaintext");

			if(c1_row == c2_row)
			{
				ciphertext[i] = grid[c1_row * gridSize + Mod(c1_col + 1, gridSize)];
				ciphertext[i + 1] = grid[c2_row * gridSize + Mod(c2_col + 1, gridSize)];
			}
			else if(c1_col == c2_col)
			{
				ciphertext[i] = grid[Mod(c1_row + 1, gridSize) * gridSize + c1_col];
				ciphertext[i + 1] = grid[Mod(c2_row + 1, gridSize) * gridSize + c2_col];
			}
			else
			{
				ciphertext[i] = grid[c1_row * gridSize + c2_col];
				ciphertext[i + 1] = grid[c2_row * gridSize + c1_col];
			}
		}

		return ciphertext;
	}

	std::string Decode(const std::string& ciphertext, const std::string& grid)
	{
		int gridSize = std::sqrt(grid.size());
		std::string plaintext(ciphertext.length() - (ciphertext.length() % 2), ' ');

		for(size_t i = 0; i < plaintext.length(); i += 2)
		{
			int c1_row = -1, c1_col = -1;
			int c2_row = -1, c2_col = -1;

			for(size_t j = 0; j < grid.length(); j++)
			{
				if(grid[j] == ciphertext[i])
				{
					c1_row = j / gridSize;
					c1_col = j % gridSize;
				}

				if(grid[j] == ciphertext[i + 1])
				{
					c2_row = j / gridSize;
					c2_col = j % gridSize;
				}

				if(c1_row != -1 && c2_row != -1)
					break;
			}

			if(c1_row == -1 || c2_row == -1)
				throw std::out_of_range("invalid character in ciphertext");

			if(c1_row == c2_row)
			{
				plaintext[i] = grid[c1_row * gridSize + Mod(c1_col - 1, gridSize)];
				plaintext[i + 1] = grid[c2_row * gridSize + Mod(c2_col - 1, gridSize)];
			}
			else if(c1_col == c2_col)
			{
				plaintext[i] = grid[Mod(c1_row - 1, gridSize) * gridSize + c1_col];
				plaintext[i + 1] = grid[Mod(c2_row - 1, gridSize) * gridSize + c2_col];
			}
			else
			{
				plaintext[i] = grid[c1_row * gridSize + c2_col];
				plaintext[i + 1] = grid[c2_row * gridSize + c1_col];
			}
		}

		return plaintext;
	}

private:
	static int Mod(int a, int b)
	{
		return ((a % b) + b) % b;
	}
};