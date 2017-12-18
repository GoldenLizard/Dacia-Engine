#pragma once

#include "DaciaGraphics.hpp"

namespace Dacia
{
	namespace Graphics
	{
		struct GpuBuffer
		{
			virtual void Init()		= 0;
			virtual void Destroy()  = 0;
			virtual void Bind()		= 0;
			virtual void Unbind()	= 0;

			GPU_Handle m_handle;
			uint64	   length;
		};
	}
}