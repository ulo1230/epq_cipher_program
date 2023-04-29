#pragma once

#include "Playfair.hpp"
#include "GridShuffler.hpp"
#include "FitnessCalculator.hpp"
#include <cassert>
#include <iostream>

class SimulatedAnnealing
{
public:

	struct Params {
		std::string initialGrid;
		size_t minIterations = 50000;
		float initialSuboptimalChangeRate = 20;
		std::string alphabet = "abcdefghijklmnopqrstuvwxy";
	};

	struct Result {
		std::string grid;
		std::string text;
		std::string initialGrid;
		float fitness;
		size_t gridIterations;
		size_t totalIterations;
	};

	SimulatedAnnealing(const std::string& referenceTextPath)
		: calculator(referenceTextPath)
	{
	}

	Result Solve(const std::string& ciphertext, const Params& params)
	{
		std::string parent = params.initialGrid.length() ? params.initialGrid : randomGrid(params.alphabet);
		std::string initialKey = parent;
		float parentFitness = calculator.Calulate(cipher.Decode(ciphertext, parent));

		std::string bestGrid = parent;
		float bestFitness = parentFitness;

		size_t iterations = 0;
		size_t bestGridIterations = 0;
		
		for(float scr = params.initialSuboptimalChangeRate; scr > 0; scr--)
		{
			#ifdef SIMULATED_ANNEALING_LOG
			std::cout << "suboptimal change rate: " << scr << std::endl;
			#endif

			for(size_t i = 0; i < params.minIterations; i++)
			{
				iterations++;

				std::string child = shuffler.Shuffle(parent);
				float childFitness = calculator.Calulate(cipher.Decode(ciphertext, child));
				float dF = childFitness - parentFitness;

				if(dF > 0)
				{
					parent = child;
					parentFitness = childFitness;
				}
				else if(dF < 0)
				{
					if(std::exp(dF / scr) > random.RandomFloat())
					{
						parent = child;
						parentFitness = childFitness;
					}
				}

				if(parentFitness > bestFitness)
				{
					bestGrid = parent;
					bestFitness = parentFitness;

					bestGridIterations = iterations;
				}
			}

			if(bestFitness == parentFitness)
			{
				break;
			}
		}

		std::string bestText = cipher.Decode(ciphertext, bestGrid);
		return { bestGrid, bestText, initialKey, calculator.Calulate(bestText), bestGridIterations, iterations };
	}

private:

	std::string randomGrid(std::string alphabet)
	{
		size_t size = std::sqrt(alphabet.length());

		static std::random_device dev;
		static std::mt19937 engine;
		std::shuffle(alphabet.begin(), alphabet.end(), engine);

		return alphabet;
	}

	Random random;
	GridShuffler shuffler;
	FitnessCalculator calculator;
	Playfair cipher;
};