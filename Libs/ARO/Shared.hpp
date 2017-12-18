
#ifdef ARO_DLL
	#ifdef _WIN32
		#ifdef ARO_EXPORT
			#define ARO_UTIL __declspec(dllexport)
			#define ARO_PRIVATE
		#else
			#define ARO_UTIL __declspec(dllimport)
			#define ARO_PRIVATE
		#endif
	#elif __GNUC__
		#define ARO_UTIL		__attribute__ ((visibility ("default")))
		#define ARO_PRIVATE		__attribute__ ((visibility ("hidden")))
	#else
		#define ARO_UTIL
		#define ARO_PRIVATE
	#endif
#else
	#define ARO_UTIL
	#define ARO_PRIVATE
#endif

#define ARO_DECLARATION _cdecl

#include <chrono>

namespace ARO
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

	typedef std::conditional<std::chrono::high_resolution_clock::is_steady,
		std::chrono::high_resolution_clock,
		std::chrono::steady_clock>::type Clock;

	typedef std::chrono::nanoseconds  ns;
	typedef std::chrono::microseconds us;
	typedef std::chrono::milliseconds ms;
	typedef std::chrono::seconds	  sec;
	typedef std::chrono::minutes	  min;
	typedef std::chrono::hours		  hrs;
}
