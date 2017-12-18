#include "FileManager.hpp"

void Dacia::FileManager::ResetDefaultPaths()
{
	m_defaultPaths.clear();
}

void Dacia::FileManager::AddDefaultPath(std::string filepath)
{
	m_defaultPaths.push_back(filepath);
}

std::string Dacia::FileManager::ReadFileContent(std::string filepath)
{
	fs::path pathToOpen;

	for (auto defaultPath : m_defaultPaths) //check for relative path
	{
		auto possiblePath = defaultPath + filepath;

		if(fs::exists(possiblePath))
			pathToOpen = possiblePath;
	}

	if (pathToOpen.empty())
		pathToOpen = filepath; //treat as absolute path
	else
		throw FileNotFound(filepath);

	try
	{
		std::ofstream source(pathToOpen);
		std::stringstream convertor;

		if (!source.is_open())
		{
			Log::Print(LOG::LOG_ERROR, "Failed to open file %s", filepath.c_str());
		}

		convertor << source.rdbuf();

		m_fileHistory.push("Read operation: " + pathToOpen.string());
		return convertor.str();
	}
	catch(std::ofstream::failure e)
	{
		Log::Print(LOG::LOG_ERROR, "I/O exception caught: %s", e.what());
		return "";
	}
}

Dacia::FileManager::FileNotFound::FileNotFound(std::string filepath):
	std::runtime_error("File not found: " + filepath)
{
}

template<typename ...args>
bool Dacia::FileManager::WriteToFile(std::string filepath, 
									 std::string format, 
									 args ...arguments)
{
}