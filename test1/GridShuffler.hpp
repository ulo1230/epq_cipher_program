#pragma once

#include <string>
#include <algorithm>
#include <cmath>
#include "Random.hpp"

class GridShuffler
{
public:
	GridShuffler()
	{	
	}

	std::string Shuffle(std::string grid)
	{
		size_t gridSize = std::sqrt(grid.length());

		float rand = random.RandomFloat();

		if(rand < 0.02)
		{
			SwapRows(grid, gridSize);
		}
		else if(rand < 0.04)
		{
			SwapColumns(grid, gridSize);
		}
		else if(rand < 0.06)
		{
			ReverseRows(grid, gridSize);
		}
		else if(rand < 0.08)
		{
			ReverseColumns(grid, gridSize);
		}
		else if(rand < 0.10)
		{
			ReverseGrid(grid, gridSize);
		}
		else
		{
			SwapCharacters(grid, gridSize);
		}

		return grid;
	}

	void SwapCharacters(std::string& grid, ssize_t gridSize = -1)
	{
		gridSize = gridSize == -1 ? std::sqrt(grid.length()) : gridSize;

		size_t i1 = random.RandomFloat() * grid.length();
		size_t i2 = (i1 + 1 + size_t(random.RandomFloat() * (grid.length() - 1))) % grid.length();
		std::swap(grid[i1], grid[i2]);
	}

	void SwapRows(std::string& grid, size_t gridSize = -1)
	{
		gridSize = gridSize == -1 ? std::sqrt(grid.length()) : gridSize;
	
		size_t r1 = size_t(random.RandomFloat() * gridSize);
		size_t r2 = (r1 + size_t(random.RandomFloat() * (gridSize - 1))) % gridSize;
		
		for(size_t c = 0; c < gridSize; c++)
		{
			std::swap(grid[r1 * gridSize + c], grid[r2 * gridSize + c]);
		}
	}

	void SwapColumns(std::string& grid, size_t gridSize = -1)
	{
		gridSize = gridSize == -1 ? std::sqrt(grid.length()) : gridSize;
		
		size_t c1 = size_t(random.RandomFloat() * gridSize);
		size_t c2 = (c1 + size_t(random.RandomFloat() * (gridSize - 1))) % gridSize;
		
		for(size_t r = 0; r < gridSize; r++)
		{
			std::swap(grid[r * gridSize + c1], grid[r * gridSize + c2]);
		}
	}

	void ReverseRows(std::string& grid, size_t gridSize = -1)
	{
		gridSize = gridSize == -1 ? std::sqrt(grid.length()) : gridSize;

		for(size_t r = 0; r < gridSize; r++)
		{
			for(size_t c = 0; c < gridSize / 2; c++)
			{
				std::swap(grid[r * gridSize + c], grid[r * gridSize + gridSize - c - 1]);
			}
		}
	}

	void ReverseColumns(std::string& grid, size_t gridSize = -1)
	{
		gridSize = gridSize == -1 ? std::sqrt(grid.length()) : gridSize;

		for(size_t c = 0; c < gridSize; c++)
		{
			for(size_t r = 0; r < gridSize / 2; r++)
			{
				std::swap(grid[r * gridSize + c], grid[(gridSize - r - 1) * gridSize + c]);
			}
		}
	}

	void ReverseGrid(std::string& grid, size_t gridSize = -1)
	{
		std::reverse(grid.begin(), grid.end());
	}

private:
	Random random;
};