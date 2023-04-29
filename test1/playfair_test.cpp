#define SIMULATED_ANNEALING_LOG
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
	std::string ciphertext = LoadCipherText("./ciphertext1.txt");

	Stopwatch sw;
	SimulatedAnnealing::Params params;
	SimulatedAnnealing solver("./reference.txt");

	params.alphabet = "abcdefghiklmnopqrstuvwxyz";
	// params.alphabet = "abcdefghijklmnopqrstuvwxy";
	params.minIterations = 50000;
	params.initialSuboptimalChangeRate = 20;

	std::vector<std::tuple<SimulatedAnnealing::Result, SimulatedAnnealing::Params, long>> results;

	std::cout << params.initialSuboptimalChangeRate << std::endl;

	{
		sw.start();
		auto solution = solver.Solve(ciphertext, params);
		auto time = sw.time();

		results.push_back({ solution, params, time });
		std::cout << "time taken: " << time << "\n" << std::endl;
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
			{ "initialSuboptimalChangeRate", settings.initialSuboptimalChangeRate },
		};

		std::cout << solution.text << std::endl;

		resultsJson.push_back(resultJson);
	}

	std::ofstream of("./output.json");
	of << resultsJson.dump();
	of.close();
}