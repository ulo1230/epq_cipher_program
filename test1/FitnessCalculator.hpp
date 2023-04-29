#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

class FitnessCalculator
{
public:
	FitnessCalculator(const std::string& referenceTextPath)
	{
		std::fstream fs(referenceTextPath);

		if(!fs)
			throw std::runtime_error("failed to open reference text file");

		std::stringstream ss;
		ss << fs.rdbuf();
		
		fs.close();

		Load(ss.str());
	}

	void Load(std::string text)
	{
		text = FilterText(text);

		if(text.length() < 4)
			throw std::runtime_error("reference text must be at least 4 characters");

		quadgrams = NgramProbalilityMap(text, 4);
		quadgramCount = text.length() - 3;
	}

	float Calulate(const std::string& text)
	{
		float score = 0;

		for(ssize_t i = 0; i < ssize_t(text.length()) - 3; i++)
		{
			float prob = 1.0f / quadgramCount;
			auto it = quadgrams.find(text.substr(i, 4));

			if(it != quadgrams.end())
				prob = it->second;

			score += std::log10(prob);
		}

		return score;
	}

private:
	char ToLower(char c)
	{
		return ('A' <= c && c <= 'Z') ? (c - 'A' + 'a') : c;
	}

	std::string FilterText(const std::string& text)
	{
		std::string filtered;

		for(char c : text)
		{
			c = ToLower(c);

			if('a' <= c && c <= 'z')
			{
				filtered += c;
			}
		}

		return filtered;
	}

	std::unordered_map<std::string, float> NgramProbalilityMap(const std::string& text, size_t n)
	{
		std::unordered_map<std::string, float> ngrams;

		for(ssize_t i = 0; i < text.length() - n + 1; i++)
			ngrams[text.substr(i, n)] += 1;

		for(auto& ngram : ngrams)
			ngram.second /= text.length() - n + 1;

		return ngrams;
	}

	std::unordered_map<std::string, float> quadgrams;
	size_t quadgramCount = 0;
};