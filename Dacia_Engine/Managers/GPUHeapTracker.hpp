#pragma once

#include <Utilities\EngineUtilities.hpp>
#include <Utilities\Skeletons.hpp>
#include <Engine.hpp>

#include <map>

namespace Dacia
{
	namespace Graphics
	{
		enum class GPUObjectType
			: byte
		{
			VERTEX_BUFFER,
			VERTEX_ATTRIB_ARRAY,
			TEXTURE_1D,
			TEXTURE_2D,
			TEXTURE_3D,
			CUBEMAP,
			FRAMEBUFFER,
			RENDERBUFFER,
			SHADER,
			SHADER_PROGRAM,
			UNIFORM,
			UNKNOWN
		};

		enum class HandleFlags
			: byte
		{
			ALIVE,
			DEAD,
			USED
		};


		struct GPUHandle
		{
			uint32		  m_id{ 0 };
			uint32		  m_refs{ 0 };
			GPUObjectType m_type{ GPUObjectType::UNKNOWN };
			byte		  m_flags{ 0 };
			int64		  m_size{ UNKNOWN };

			bool IsAlive();
			bool IsValid();

			void SignalCreation();
			void SignalDeath();
		};

		class GPUHeapTracker :
			public Skeletons::Unique
		{
			struct ObjectStillInUse :
				public std::runtime_error
			{
				explicit ObjectStillInUse(const char *);
				explicit ObjectStillInUse(std::string const &);
			};

			struct HeapLeaking :
				public std::runtime_error
			{
				explicit HeapLeaking(const char *);
				explicit HeapLeaking(std::string const &);
			};

			std::unordered_map<uint32, GPUHandle> m_heapContent;

		public:

			GPUHeapTracker();
			GPUHeapTracker(DriverOptions);

			void EventLoop();

			void RegisterObject(GPUHandle objectHandle);

			void AddToHeap(uint32 id);
			void AddToHeap(GPUHandle objectHandle);

			void RemoveFromHeap(GPUHandle objectHandle);
			void RemoveFromHeap(uint32 id);

			bool Exists(uint32 objectID);

			void IncreaseReference(uint32 id);
			void DecreaseReference(uint32 id);

		private:

			void OnObjectDeath(uint32 objectID);
			void OnObjectCreation(uint32 objectID);
		};
	}
}