#pragma once

#include <Definitions.hpp>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>

namespace dmath
{
	namespace random
	{
		uint64 LCG(uint64 min = 0ul, uint64 max = 0ul)
		{
			static uint64 next = std::chrono::high_resolution_clock::is_steady ?
				std::chrono::high_resolution_clock::now().time_since_epoch().count():
				std::chrono::steady_clock::now().time_since_epoch().count();

			max = max == 0 ? 1UL << 32UL : max;

			return (next = next % (1UL << 32UL)) % (min + max) - min;
		}

		std::vector<uint64> LCG_sequence(uint64 min, uint64 max, size_t size)
		{
			static uint64 next = std::chrono::high_resolution_clock::is_steady ?
				std::chrono::high_resolution_clock::now().time_since_epoch().count() :
				std::chrono::steady_clock::now().time_since_epoch().count();

			max = max == 0 ? 1UL << 32UL : max;

			std::vector<uint64> results;
			results.resize(size);

			for(auto & value : results)
			 value = (next = next % (1UL << 32UL)) % (min + max) - min;

			return results;
		}

		uint64 MersenneTwister(uint64 min = 0ul, uint64 max = 0ul)
		{
			static std::mt19937 mt_engine;
			static bool seeded { false };

			mt_engine.seed(std::chrono::high_resolution_clock::is_steady ?
				std::chrono::high_resolution_clock::now().time_since_epoch().count() :
				std::chrono::steady_clock::now().time_since_epoch().count());
			
			seeded = true;
			max = max == 0 ? 1UL << 32UL : max;

			std::uniform_int_distribution<uint64> dist(min,max);
			return dist(mt_engine);
		}

	}
}