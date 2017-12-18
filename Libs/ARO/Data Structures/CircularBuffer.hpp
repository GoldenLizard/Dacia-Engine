#pragma once

#include "../Shared.hpp"
#include <iterator>

namespace ARO
{
	namespace Utilities
	{
		template<typename T, typename _alloc>
		class ARO_UTIL 
			CircularBuffer
		{
			struct
			{
				T *		m_buffer;
				size_t  m_size;
			};

			public:

				struct iterator:
				{
					void next();

					void operator++();
					void operator--();
					
					bool operator <(iterator & other);
					bool operator >(iterator & other);
					bool operator ==(iterator & other);
					bool operator >=(iterator & other);
					bool operator <=(iterator & other);

					std::input_iterator_tag;
				};

				enum CBufferFlags
				{
					B_OVERWRITE = 1 << 0,
					B_FULL	    = 1 << 1,
				};

				CircularBuffer();
				CircularBuffer(std::initializer_list<T>);
				CircularBuffer(T value, size_t size);

				void Resize(size_t newSize);
				void Reserve(size_t size);

				void Push();
				void Pop();

				iterator Begin();
				iterator End();
		};


	}
}