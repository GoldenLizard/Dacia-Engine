#pragma once

#include "Common.hpp"
#include "Assertions.hpp"


#define STR(content)	(#content)
#define WIDE(content)	{ L ## content}									   

namespace Dacia
{
	namespace Utility
	{
		template<typename _pchar>
		struct StringWrapper
		{
			typedef typename
			std::basic_string<_pchar> str;

			static constexpr size_t GLYPH_SIZE = sizeof(_pchar);
			static  str		Convert(const char * _cstring);
			static _pchar	Convert(const char _char);
		};

		template<typename _pchar>
		inline typename StringWrapper<_pchar>::str
			StringWrapper<_pchar>::Convert(const char * _cstring)
		{
			return str(_cstring);
		}

		template<typename _pchar>
		inline _pchar 
		StringWrapper<_pchar>::Convert(const char _char)
		{
			Assert::Convertible<_pchar, wchar_t>();
			return std::static_cast<wchar_t>(_char);
		}

		template<>
		inline char StringWrapper<char>::Convert(const char _char)
		{
			return _char;
		}

	}
}