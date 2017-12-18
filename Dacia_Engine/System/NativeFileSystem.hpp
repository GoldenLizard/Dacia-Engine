#pragma once

#include "OSGeneral.hpp"

namespace Dacia
{
	namespace System
	{
		
		/****************************
		*! Checks if a filename exists
		*@return: true if file exists
		*@param1: possible filename
		*****************************/
		template<typename _pchar, size_t size>
		bool FileExists(_pchar (&filename)[size]);

		/****************************
		*! Removes a file if it exists
		*@return: true if operation succeds
		*@param1: possible filename
		*****************************/
		template<typename _pchar, size_t size>
		bool RemoveFileNative(_pchar(&filename)[size]);
		
		/****************************
		*! Creates a file with the specified name
		*@return: true if operation succeds
		*@param1: possible filename
		*****************************/
		template<typename _pchar, size_t size>
		bool CreateFileNative(_pchar(&filename)[size]);

		/****************************
		*! Creates a file with the specified name
		*@return: true if operation succeds
		*@param1: possible filename
		*****************************/
		template<typename _pchar, size_t size>
		bool CreateDirectoryNative(_pchar(&dirname)[size]);

		/****************************
		*! Removes a directory and all its contents recursively 
		*! with the specified name
		*@return: true if operation succeds
		*@param1: possible filename
		*****************************/
		template<typename _pchar, size_t size>
		bool RemoveDirectoryNative(_pchar(&dirname)[size]);
	}
}