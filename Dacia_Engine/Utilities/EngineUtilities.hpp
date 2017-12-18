#pragma once

#include <Utilities\Common.hpp>

#include <Dacia.Math\Definitions.hpp>

#include <Utilities\Skeletons.hpp>
#include <Utilities\Assertions.hpp>
#include <IO\LogStream.hpp>

namespace Dacia
{
	int64 constexpr UNKNOWN = -1;
	static struct
	{
		inline
		Log::LogStream<> & operator()()
		{
			static Log::LogStream<> __engineLog({ &std::cout, /*&std::ofstream("log.txt")*/ });
			return __engineLog;
		}

	} __globalLog;

	namespace Log {

		constexpr uint16 LOG_SIZE = 1024;

		template<typename size_t size, typename ...args>
		void inline Print(LogLevel level, char const(&message)[size], args ...arguments)
		{
			return __globalLog().Print(level, message, arguments...);
		}
	}
}
