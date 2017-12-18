#pragma once

#include <Shared.hpp>
#include <ostream>

namespace ARO
{
	namespace Log
	{
		enum class LogLevel : byte
		{
			LOG_DEBUG,
			LOG_WARNING,
			LOG_ERROR,
			LOG_FATAL,
			LOG_MINOR,
			LOG_MEDIUM,
			LOG_MAJOR,
			LOG_GRAPHICS,
			LOG_GAMEPLAY
		};

		constexpr char * ARG[] = 
		{ "%",  "$",  "#",
		  "d",  "f",  "i",
		  "u",  ".",  "llu",
		  "ll"  "arg" "arg[]"};

		template<typename ...Args>
		std::string ParseLogPrint(std::string comment, Args ... args);

		template<typename ...Args>
		std::wstring ParseLogPrint(std::wstring comment, Args ... args);
		

		template<typename _glyph,
				 typename _traits = std::char_traits<_glyph>>
		class LogBuffer:
			public std::basic_streambuf<_glyph, _traits>
		{

		};

		template<typename _glyph,
				 typename _traits = std::char_traits<_glyph>>
		class LogStream :
			public std::basic_ostream<_glyph, _traits>
		{
			//const static _iobuf * STDOUT{stdout};
			//const static _iobuf * STDERR{stderr};
			//const static _iobuf * STDLOG{stdout};

			public:

				void LogFile();
		};

	}
}