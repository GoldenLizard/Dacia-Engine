#if defined(_WIN32) && defined(ARO_DLL)

#include "Shared.hpp"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

BOOL _stdcall DLLMain(HINSTANCE hDllARO, 
					  DWORD reason, 
					  LPVOID lpReserved)
{
	switch (reason)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		};

		case DLL_PROCESS_DETACH:
		{
			break;
		};

		case DLL_THREAD_ATTACH:
		{
			break;
		};

		case DLL_THREAD_DETACH:
		{
			break;
		};

	}

	return TRUE;
}

#endif