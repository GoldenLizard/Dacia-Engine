#pragma once

#include <Utilities\Common.hpp>

namespace Dacia
{
	namespace System
	{
		class OS_Specs;
		class Console;
		class Dialog;
		class Widget;

		enum class OSType : byte
		{
			UNKNOWN,
			WINDOWS_32,
			WINDOWS_64,
			LINUX_32,
			LINUX_64,
			UNIX
		};

		//constexpr OSType GetCurrentOS()
		//{
		//	
		//}

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