#pragma once

#include "LogStream.hpp"

template<typename ...Args>
std::string ARO::Log::ParseLogPrint(std::string comment, Args ...args)
{
	size_t index = 0;
	const size_t size = sizeof...(args...);

	std::tuple<Args...> arguments;

	for (auto a : arguments)
	{

	}

}