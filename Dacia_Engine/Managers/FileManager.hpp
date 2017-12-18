#pragma once

#include <Utilities\EngineUtilities.hpp>
#include <IO\File.hpp>
#include <experimental\filesystem>
#include <fstream>
#include <queue>
#include <unordered_set>

namespace Dacia
{
	namespace fs = std::experimental::filesystem;

	template<typename _hashFunc>
	class FileCatalogue
	{

	};

	class FileManager:
		public Skeletons::Unique
	{
		struct FileNotFound : public std::runtime_error
		{
			explicit FileNotFound(std::string filepath);
		};

		//OS currentFileSystem;

		std::vector<std::string>	m_defaultPaths;
		std::queue<std::string>		m_fileHistory;

		public:

			/*bool static CreateAndOpenFile(Path);
			bool static CreateAndWriteFile(Path);
			bool static CreateTemporaryFile(Path);
			bool static CreateTempAndWrite(Path);*/

			template<typename ...args>
			bool WriteToFile(std::string filepath, 
				std::string format, args ...arguments);

			void ResetDefaultPaths();
			void AddDefaultPath(std::string filepath);

			std::string ReadFileContent(std::string filepath);
			

	};

}
