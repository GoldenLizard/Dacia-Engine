#pragma once

#include <Utilities\Common.hpp>

/*TO DO: make streams thread safe*/

namespace Dacia
{
	namespace Log
	{
		enum class LogLevel : byte
		{
			LOG_DEBUG,
			LOG_WARNING,
			LOG_ERROR,
			LOG_MINOR,
			LOG_MEDIUM,
			LOG_MAJOR,
			LOG_GRAPHICS,
			LOG_GAMEPLAY
		};

		static const std::vector<std::string>	k_levelLog
		{
			"DEBUG : ",
			"WARNING : ",
			"ERROR : ",
			"MINOR : ",
			"MEDIUM : ",
			"MAJOR : ",
			"GRAPHICS : ",
			"GAMEPLAY : "
		};

		static const std::vector<std::wstring>	k_wlevelLog
		{
			L"DEBUG : ",
			L"WARNING : ",
			L"ERROR : ",
			L"MINOR : ",
			L"MEDIUM : ",
			L"MAJOR : ",
			L"GRAPHICS : ",
			L"GAMEPLAY : "
		};

		template<typename glyph = char, typename traits = std::char_traits<glyph>>
		class LogBuffer :
			public std::basic_streambuf<glyph, std::char_traits<glyph>>
		{
			typedef std::basic_ostream<glyph, std::char_traits<glyph>> outStream;

		public:

			explicit LogBuffer(std::initializer_list<outStream*> outputs);

			virtual int overflow(int_type)	override;
			virtual int sync()				override;

			int RemoveBuffer(outStream *);

			void AddBuffer(outStream*);
			void RemoveBuffer(bool isFirst);
			void RemoveAllBuffers();

		protected:

			std::vector<std::basic_streambuf<glyph>*>	m_outputBuffers;
			//std::vector<std::array<glyph, bufferSize>>	m_charBuffers;
		};

		template<typename glyph = char, size_t bufferSize = 1024u>
		class LogStream :
			public std::basic_ostream<glyph, std::char_traits<glyph>>
		{
			typedef std::basic_ostream<glyph, std::char_traits<glyph>> outStream;

		public:
			explicit LogStream(std::initializer_list<outStream*> outputs);

			template<size_t size, typename ...args>
			void Print(LogLevel level, glyph const (&message)[size], args ... arguments);

			template<size_t size, typename ...args>
			void PrintW(LogLevel level, glyph const (&message)[size], args ... arguments);

			void CreateLogFile();
			void SetBuffer();
			void Flush();

			void AddBuffer(outStream*);
			int RemoveBuffer(outStream*);

			void RemoveLastBuffer();
			void RemoveFirstBuffer();
			void RemoveAllBuffers();

		protected:

			LogBuffer<glyph, std::char_traits<glyph>>	m_streamBuffer;
		};


		template<typename glyph, typename traits>
		LogBuffer<glyph, traits>::LogBuffer(std::initializer_list<outStream*> outputs)
		{
			std::ios::sync_with_stdio(false);
			m_outputBuffers.reserve(outputs.size());

			for (auto output : outputs)
			{	
				auto buf = output->rdbuf();

				m_outputBuffers.push_back(buf);
			}
		}

		template<typename glyph, typename traits>
		int LogBuffer<glyph, traits>::overflow(int_type ctype)
		{
			traits::int_type const eof = traits::eof();

			if (traits::eq_int_type(ctype, eof))
				return traits::not_eof(ctype);
			else
			{
				traits::char_type const type = traits::to_char_type(ctype);
				bool result = true;
				int isEof = 0;

				for (auto buffer : m_outputBuffers)
				{
					int isEof = buffer->sputc(ctype);
					if (isEof == eof)
						result = false;
				}

				return result ? ctype : eof;
			}

			return 0;
		}

		template<typename glyph, typename traits>
		int LogBuffer<glyph, traits>::sync()
		{
			int result = 0;

			for (auto buffer : m_outputBuffers)
				result &= (buffer->pubsync()) != 0 ? 1 : 0;

			return result == 0 ? 0 : -1;
		}

		template<typename glyph, typename traits>
		inline void LogBuffer<glyph, traits>::AddBuffer(outStream * buffer)
		{
			this->m_outputBuffers.push_back(buffer->rdbuf());
		}

		template<typename glyph, typename traits>
		inline void LogBuffer<glyph, traits>::RemoveBuffer(bool isFirst)
		{
			return isFirst ? this->m_outputBuffers.erase(m_outputBuffers.front()) :
				this->m_outputBuffers.pop_back();
		}

		template<typename glyph, typename traits>
		inline void LogBuffer<glyph, traits>::RemoveAllBuffers()
		{
			m_outputBuffers.clear();
		}

		template<typename glyph, typename traits>
		inline int LogBuffer<glyph, traits>::RemoveBuffer(outStream * __Buffer)
		{
			auto iter = 0u;
			for (auto buffer : m_outputBuffers)
			{
				if (uintptr_t(buffer) == uintptr_t(__Buffer->rdbuf()))
				{
					this->m_outputBuffers.erase(this->m_outputBuffers.begin() + iter);
					return 0;
				}
				++iter;
			}

			return 1;
		}


		template<typename glyph, size_t bufferSize>
		LogStream<glyph, bufferSize>::LogStream(std::initializer_list<outStream*> outputs) :
			outStream(&m_streamBuffer),
			m_streamBuffer(outputs)
		{
		}

		template<typename glyph, size_t bufferSize>
		void LogStream<glyph, bufferSize>::CreateLogFile()
		{
		}

		template<typename glyph, size_t bufferSize>
		void LogStream<glyph, bufferSize>::SetBuffer()
		{

		}

		template<typename glyph, size_t bufferSize>
		void LogStream<glyph, bufferSize>::Flush()
		{
			this->operator<<(std::flush);
		}

		template<typename glyph, size_t bufferSize>
		inline void LogStream<glyph, bufferSize>::AddBuffer(outStream * buffer)
		{
			m_streamBuffer.AddBuffer(buffer);
		}

		template<typename glyph, size_t bufferSize>
		inline int LogStream<glyph, bufferSize>::RemoveBuffer(outStream * buffer)
		{
			return m_streamBuffer.RemoveBuffer(buffer);
		}

		template<typename glyph, size_t bufferSize>
		inline void LogStream<glyph, bufferSize>::RemoveLastBuffer()
		{
			m_streamBuffer.RemoveBuffer(false);
		}

		template<typename glyph, size_t bufferSize>
		inline void LogStream<glyph, bufferSize>::RemoveFirstBuffer()
		{
			m_streamBuffer.RemoveBuffer(true);
		}

		template<typename glyph, size_t bufferSize>
		inline void LogStream<glyph, bufferSize>::RemoveAllBuffers()
		{
			m_streamBuffer.RemoveAllBuffers();
		}

		template<typename glyph, size_t bufferSize>
		template<size_t size, typename ...args>
		void LogStream<glyph, bufferSize>::Print(LogLevel level, glyph const(&message)[size], args ...arguments)
		{
			std::string levelStr = "DEBUG : ";

			if(uint8_t(level) < k_levelLog.size())
				levelStr = k_levelLog[uint8_t(level)];

			glyph buffer[bufferSize]{ 0 };

			this->write(levelStr.c_str(), levelStr.size());
			sprintf_s(buffer, bufferSize, message, arguments...);
			this->write(buffer, std::strlen(buffer));
			this->operator<<(std::endl);
		}

		template<typename glyph, size_t bufferSize>
		template<size_t size, typename ...args>
		void LogStream<glyph, bufferSize>::PrintW(LogLevel level, glyph const(&message)[size], args ...arguments)
		{
			std::wstring levelStr = L"DEBUG : ";

			if (uint8_t(level) < k_levelLog.size())
				levelStr = k_wlevelLog[uint8_t(level)];

			glyph buffer[bufferSize]{ 0 };

			this->write(levelStr.c_str(), levelStr.size());

			swprintf_s(buffer, bufferSize, message, arguments...);
			this->write(buffer, std::wcslen(buffer));
			this->write("\n");

			this->flush();
		}

	}
}

typedef Dacia::Log::LogLevel LOG;