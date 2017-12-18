#pragma once

#include <Utilities\Common.hpp>

namespace Dacia
{
	namespace System
	{
		class Console;
		class Dialog;
		class Widget;

		enum class OSType : byte
		{
			WINDOWS,
			LINUX,
			UNIX
		};

		constexpr OSType GetCurrentOS()
		{
			#ifdef _WIN32
				return OSType::WINDOWS;
			#endif
		}

		enum class MsgBoxOption : byte
		{
			OK,	YES, NO,
			CANCEL,	ABORT,
			RETRY, EXIT
		};

		enum class MsgBoxTemplate : byte
		{
			OK, YES_NO, 
			YES_NO_CANCEL
		};

		template<typename _glyph = char, typename ...args>
		MsgBoxOption CreateMessageBox(std::string message, std::string caption,
									  MsgBoxTemplate = MsgBoxTemplate::OK);
		


	}
}