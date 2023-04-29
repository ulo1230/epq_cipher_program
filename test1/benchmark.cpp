#include "SimulatedAnnealing.hpp"
#include "stopwatch.hpp"
#include "json.hpp"

#include <iostream>
#include <cassert>
#include <sstream>
#include <tuple>

using json = nlohmann::json;

std::string LoadCipherText(const std::string& path)
{
	std::fstream fs(path);
	assert(fs);
	std::stringstream ss;
	ss << fs.rdbuf();
	return ss.str();
}

int main()
{
	std::string ciphertext = LoadCipherText("./ciphertext.txt");

	Stopwatch sw;
	SimulatedAnnealing::Params params;
	SimulatedAnnealing solver("./reference.txt");

	params.minIterations = 30000;
	params.suboptimalChangeFactor = 1;

	std::vector<std::tuple<SimulatedAnnealing::Result, SimulatedAnnealing::Params, long>> results;

	for( ; params.suboptimalChangeFactor <= 20; params.suboptimalChangeFactor += 1)
	{
		std::cout << params.suboptimalChangeFactor << std::endl;
		for(int i = 1; i <= 50; i++)
		{
			std::cout << "Solving (" << i << ")..." << std::endl;

			sw.start();
			auto solution = solver.Solve(ciphertext, params);
			auto time = sw.time();

			results.push_back({ solution, params, time });
			std::cout << "time taken: " << time << "\n" << std::endl;
		}
	}

	json resultsJson = json::array();

	for(auto& result : results)
	{
		SimulatedAnnealing::Result& solution = std::get<0>(result);
		SimulatedAnnealing::Params& settings = std::get<1>(result);
		long time_ms = std::get<2>(result);

		json resultJson = {
			{ "grid", solution.grid },
			{ "text", solution.text },
			{ "fitness", solution.fitness },
			{ "gridIterations", solution.gridIterations },
			{ "totalIterations", solution.totalIterations },
			{ "initialGrid", solution.initialGrid },
			{ "time", time_ms },

			{ "minIterations", settings.minIterations },
			{ "suboptimalChangeFactor", settings.suboptimalChangeFactor },
		};

		resultsJson.push_back(resultJson);
	}

	std::ofstream of("./output.json");
	of << resultsJson.dump();
	of.close();
}