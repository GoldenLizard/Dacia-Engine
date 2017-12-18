#pragma once

#include <Utilities\Common.hpp>
#include <Utilities\EngineUtilities.hpp>
#include <Graphics\DaciaGraphics.hpp>

namespace Dacia
{

	struct ObjectContent
	{
		uint32			id;
		uint32			references;
		GPUObjectType	type;
		int64			sizeInBytes;
		std::string		pathOnDisk;
		void *			extraData;

		std::string LogInfo();
	};

	class MemoryAllocationTracker : 
		public Skeletons::Unique
	{
		static uint32 idCounter;

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

		public:

			void SignalObjectCreation(GPUObjectType, int64 size, void * extraData = nullptr);
			void SignalObjectDeath(uint32 id);

			void RegisterObject(ObjectContent objContent);
			void UnregisterObject(uint32 id);
			
			bool IsUsed(uint32 id);
			bool IsEmpty();

			void OnCleanUp();
	
		private:

			void AddToHeap(ObjectContent objContent);
			void AddToHeap(uint32 id, GPUObjectType,
							int64 size,
							std::string path = "",
							void * extraData = nullptr);
			
			void RemoveFromHeap(uint32 id);
	
			std::unordered_map<uint32, ObjectContent> m_heapContent;
			void IncreaseReference(uint32 id);
			void DecreaseReference(uint32 id);
	};

}