#include <unordered_map>
#include <random>
#include <iostream>

#include "TestUtils.hpp"

std::unordered_map<char, int> MakeAlphabetMap(const std::string& alphabet)
{
	std::unordered_map<char, int> alphabetMap;

	for(size_t i = 0; i < alphabet.length(); i++)
		alphabetMap[alphabet[i]] = i;

	return alphabetMap;
}

// creates alphabet map
std::string Solve1(const std::string& input, const std::string& alphabet)
{
	auto map = MakeAlphabetMap(alphabet);
	std::string output(input.length(), ' ');

	for(size_t i = 0; i < input.length(); i++)
	{
		int index = map.at(input[i]);
		output[i] = alphabet[(index + 1) % alphabet.length()];
	}

	return output;
}

// given alphabet map
std::string Solve2(const std::string& input, const std::unordered_map<char, int>& map, const std::string& alphabet)
{
	std::string output(input.length(), ' ');

	for(size_t i = 0; i < input.length(); i++)
	{
		int index = map.at(input[i]);
		output[i] = alphabet[(index + 1) % alphabet.length()];
	}

	return output;
}

// uses index
std::string Solve3(const std::string& input, const std::string& alphabet)
{
	std::string output(input.length(), ' ');

	for(size_t i = 0; i < input.length(); i++)
	{
		int index = alphabet.find(input[i]);
		output[i] = alphabet[(index + 1) % alphabet.length()];
	}

	return output;
}

int main()
{
	const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	Stopwatch stopwatch;

	const std::string inputText = MakeText(100, alphabet);
	size_t count = 10000000;


	// solve 1
	{
		stopwatch.start();
		
		for(size_t i = 0; i < count; i++)
		{
			Solve1(inputText, alphabet);
		}

		std::cout << "Solve 1: " << stopwatch.time() * 1000 << std::endl;
	}


	// solve 2
	{
		auto alphabetMap = MakeAlphabetMap(alphabet);

		stopwatch.start();
		
		for(size_t i = 0; i < count; i++)
		{
			Solve2(inputText, alphabetMap, alphabet);
		}

		std::cout << "Solve 2: " << stopwatch.time() * 1000 << std::endl;
	}

	// solve 3
	{
		stopwatch.start();
		
		for(size_t i = 0; i < count; i++)
		{
			Solve3(inputText, alphabet);
		}

		std::cout << "Solve 3: " << stopwatch.time() * 1000 << std::endl;
	}
}