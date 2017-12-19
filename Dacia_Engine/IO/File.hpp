#pragma once

#include <Utilities\EngineUtilities.hpp>
#include <Utilities\StringUtils.hpp>
#include <System\OSGeneral.hpp>
#include <sstream>
#include <exception>

namespace Dacia
{
	namespace IO
	{
		namespace fs = std::experimental::filesystem;
		fs::path;

		template<typename _pchar = char>
		struct Path
		{
			static constexpr _pchar SEPARATORS[]
			{ _pchar('/'), 
			  _pchar('\\'), 
			  _pchar('.') };

			Path(std::basic_string<_pchar> filepath);
			Path();

			//add common ancestor here?
			Path CommonAncestor(Path & otherPath);

			std::basic_string<_pchar> ToString();
			std::basic_string<_pchar> GetRootFolder();
			std::basic_string<_pchar> GetExtension();

			bool IsFile();
			bool Exists();

		private:

			std::basic_string<_pchar> RetrieveExtension();
			std::basic_string<_pchar> RetrieveFullName();
			std::basic_string<_pchar> RetrieveNameOnly();

			std::basic_string<_pchar> m_filepath	{ std::basic_string<_pchar>("") };
		};

		enum class FileState : byte
		{
			INVALID		= 0,
			EXISTS		= 1 << 0,
			DELETED		= 1 << 1,
			TEMP		= 1 << 2,
			OPEN		= 1 << 3,
			CORRUPTED	= 1 << 4
		};

		enum class OpenMode : byte
		{
			CLOSED			= 0,
			APPEND_END		= 1 << 0,
			APPEND_BEGIN	= 1 << 1,
			TRUNCATE		= 1 << 2,
			READ			= 1 << 3,
			WRITE			= 1 << 4,
			READ_WRITE		= READ | WRITE,
			BINARY			= 1 << 5,
			READ_BINARY		= BINARY | READ,
			WRITE_BINARY	= BINARY | WRITE,
			RW_BINARY		= READ_BINARY | WRITE_BINARY
		};

		template<typename _pchar = char>
		class File
		{
			public:

				struct InvalidFileOperation:
					public std::runtime_error
				{
					explicit inline InvalidFileOperation(std::string const & msg):
						std::runtime_error(msg)
					{}

					explicit inline InvalidFileOperation(std::wstring const & msg):
						std::runtime_error(msg)
					{}
				};

				struct FailedFileOperation:
					public std::runtime_error
				{
					explicit inline FailedFileOperation(std::string const & msg):
						std::runtime_error(msg)
					{}

					explicit inline FailedFileOperation(std::wstring const & msg):
						std::runtime_error(msg)
					{}
				};

			private:

				std::ios::_Fmtflags DaciaFlagsToCppIos();

				bool inline ResetOpenFlags()
				{
					m_openMode = OpenMode::CLOSED;
				};

				Path<_pchar>	m_path			{ std::basic_string<_pchar>("") };
				size_t			m_fileSize		{0U};

				FileState	    m_fileState		{FileState::INVALID};
				OpenMode		m_openMode		{OpenMode::CLOSED};

				std::basic_string<_pchar> m_extension	{ std::basic_string<_pchar>("") };
				std::basic_string<_pchar> m_name		{ std::basic_string<_pchar>("") };

				std::basic_fstream<_pchar, std::char_traits<_pchar>>	m_fileStream;

			public:

				File(std::basic_string<_pchar> path, bool createFile = true, bool isTemporary = false);
				File(Path<_pchar> path, bool createFile = true, bool isTemporary = false);

				~File();

				/*check if the file is open*/
				bool inline IsOpen() const;

				/*checks if the file actually exists*/
				bool inline Exists() const;

				/*gets file's root folder*/
				std::basic_string<_pchar> GetRootFolder() const;

				static std::basic_string<_pchar> FindCommonAncestor(File & f1, File & f2);
				std::basic_string<_pchar> FindCommonAncestor(File& other) const;

				/*
				@return value: operation succeded
				*/
				bool Remove();

				/*
					@return value : operation succeded
					@param1: content to write to file
					@param2: open mode if the file is not opened 
				*/
				bool WriteToFile(std::basic_string<_pchar> content, 
								 OpenMode = OpenMode::WRITE);

				/*
					@return value : operation succeded
					@param1: content to write to file
					@param2: offset to change file pointer (i.e: where to insert content)
					@param3: open mode if the file is not opened
				*/
				bool WriteToFile(std::basic_string<_pchar> content, 
								 size_t offset, 
								 OpenMode = OpenMode::WRITE);

				bool WriteAndClose(std::basic_string<_pchar> content,
					OpenMode = OpenMode::WRITE);

				bool WriteAndClose(std::basic_string<_pchar> content,
								   size_t offset,
								   OpenMode = OpenMode::WRITE);

				File		Copy(std::string path);
				std::string Move(std::string path);

				bool Open(OpenMode);
				bool Close();

				std::string ReadContent();
				std::string ReadContentAndClose();

				std::string GetName()		const;
				std::string GetOnlyName()	const;

};

	/*	FileState operator|=(FileState & f1, FileState f2)
		{
			return (f1 = static_cast<FileState>(static_cast<byte>(f1) | static_cast<byte>(f2)));
		}

		FileState operator&=(FileState & f1, FileState f2)
		{
			return (f1 = static_cast<FileState>(static_cast<byte>(f1) & static_cast<byte>(f2)));
		}

		FileState operator^=(FileState & f1, FileState f2)
		{
			return (f1 = static_cast<FileState>(static_cast<byte>(f1) ^ static_cast<byte>(f2)));
		}

		FileState operator|(FileState f1, FileState f2)
		{
			return f1 |= f2;
		}

		FileState operator&(FileState f1, FileState f2)
		{
			return f1 &= f2;
		}

		FileState operator^(FileState f1, FileState f2)
		{
			return f1 ^= f2;
		}

		OpenMode operator|=(OpenMode & openMode1, OpenMode openMode2)
		{
			return (openMode1 = static_cast<OpenMode>
				(static_cast<byte>(openMode1) | static_cast<byte>(openMode2)));
		}

		OpenMode operator&=(OpenMode & openMode1, OpenMode openMode2)
		{
			return (openMode1 = static_cast<OpenMode>
				(static_cast<byte>(openMode1) & static_cast<byte>(openMode2)));
		}

		OpenMode operator^=(OpenMode & openMode1, OpenMode openMode2)
		{
			return (openMode1 = static_cast<OpenMode>
				(static_cast<byte>(openMode1) ^ static_cast<byte>(openMode2)));
		}

		OpenMode operator|(OpenMode openMode1, OpenMode openMode2)
		{
			return openMode1 |= openMode2;
		}

		OpenMode operator&(OpenMode openMode1, OpenMode openMode2)
		{
			return openMode1 &= openMode2;
		}

		OpenMode operator^(OpenMode openMode1, OpenMode openMode2)
		{
			return openMode1 ^= openMode2;
		}*/

		template<typename _pchar>
		bool inline File<_pchar>::IsOpen() const
		{
			return m_fileState &= FileState::OPEN;
		}

		template<typename _pchar>
		bool inline File<_pchar>::Exists() const
		{
			return m_fileState &= FileState::EXISTS;
		}
	}
}