#pragma once

#include <vector>
#include <array>
#include <unordered_map>
#include <thread>
#include <memory>
#include <exception>

#include <iostream>
#include <fstream>
#include <experimental\filesystem>
#include <cwchar>

#include <3rd Party\include\glad\glad.h>
#include <glfw\include\GLFW\glfw3.h>

#define DACIA_DEBUG 1

#ifdef _WIN32
	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif
	#include <Windows.h>
#endif


namespace Dacia
{

	typedef unsigned char byte;

	typedef unsigned char		uint8;
	typedef short unsigned int	uint16;
	typedef long unsigned int	uint32;
	typedef long long unsigned  uint64;

	typedef signed char			int8;
	typedef short int			int16;
	typedef long int			int32;
	typedef long long int		int64;

}