#include "File.hpp"

template<typename _char>
bool Dacia::IO::File<typename _char>::Remove()
{
	if (IsOpen())
	{
		if (!Close())
		{
			std::string msg = "Failed to close file " + m_path.ToString();
			Log::Print(LOG::LOG_ERROR, msg.c_str());
			throw FailedFileOperation(msg);
		};
	}

	auto status = std::remove(m_path.ToString().c_str());
	
	if (status)
	{
		m_fileState |=  FileState::DELETED;
		m_fileState &= ~FileState::EXISTS;
		return true;
	}

	Log::Print(LOG::LOG_ERROR, "Failed to delete file: %s", m_path.ToString());
	return false;
}

template<typename _pchar>
Dacia::IO::Path<_pchar>::Path(std::basic_string<_pchar> filepath):
	m_filepath(filepath)
{

}

template<typename _pchar>
Dacia::IO::Path<_pchar> Dacia::IO::Path<_pchar>::CommonAncestor(Path<_pchar> & otherPath)
{
	auto pathFile1 = m_path.ToString();
	auto pathFile2 = otherPath.m_path.ToString();

	if (pathFile1 == pathFile2)
		return pathFile1.substr(pathFile1.size() - f1.GetName().size(),
			pathFile1.size());

	size_t maxSize = pathFile1.size() > pathFile2.size ?
		pathFile1.size() : pathFile2.size();

	std::basic_string<_pchar> commonAncestor = "";

	for (auto iter1 = pathFile1.begin(), iter2 = pathFile2.begin();
		*iter1 == *iter2; ++iter1, ++iter2)
		commonAncestor += *iter1;

	if (!commonAncestor.empty() &&
		commonAncestor.back() != '/')
	{
		auto index = commonAncestor.size() - 1;
		for (auto iter = commonAncestor.end();
			iter != commonAncestor.begin(); --iter)
		{
			if (*iter == SEPARATORS[0] || *iter == SEPARATORS[1])
				break;

			++index;
		}

		return commonAncestor.substr(0, index);
	};

	return commonAncestor;
}

template<typename _pchar>
std::basic_string<_pchar> Dacia::IO::Path<_pchar>::ToString()
{
	return m_filepath;
}

template<typename _pchar>
std::basic_string<_pchar> Dacia::IO::Path<_pchar>::GetRootFolder()
{
	return m_filepath.substr(0, m_filepath.size() - m_name.size());
}

template<typename _pchar>
std::basic_string<_pchar> Dacia::IO::Path<_pchar>::GetExtension()
{
	return m_extension;
}

template<typename _pchar>
Dacia::IO::File<_pchar>::File(Path<_pchar> path, bool createFile, bool isTemporary)
{
}

template<typename _pchar>
bool Dacia::IO::File<_pchar>::WriteToFile(std::basic_string<_pchar> content, size_t offset, OpenMode)
{
	if (!IsOpen())
	{
		if (!Open())
		{
			std::string msg = "Failed to open file " + m_path.ToString();
			Log::Print(LOG::LOG_ERROR, msg.c_str());
			throw FailedFileOperation(msg);
		}
	}
	
	m_fileStream.write();
	Log::Print();
}
