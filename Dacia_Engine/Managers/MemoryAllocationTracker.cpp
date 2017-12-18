#include "MemoryAllocationTracker.hpp"

Dacia::uint32 Dacia::MemoryAllocationTracker::idCounter = 0u;

void Dacia::MemoryAllocationTracker::IncreaseReference(uint32 id)
{
	std::unordered_map<uint32, ObjectContent>::iterator object;
	if ((object = m_heapContent.find(id)) == m_heapContent.end())
	{
		Log::Print(LOG::LOG_WARNING, "%u is not a valid object id", id);
		return;
	}

	++object->second.references;
}

void Dacia::MemoryAllocationTracker::DecreaseReference(uint32 id)
{
	std::unordered_map<uint32, ObjectContent>::iterator object;
	if ((object = m_heapContent.find(id)) == m_heapContent.end())
	{
		Log::Print(LOG::LOG_WARNING, "%u is not a valid object id", id);
		return;
	}

	if (object->second.references > 1)
		--object->second.references;
	else
	{	
		object->second.references = 0;
		RemoveFromHeap(id);
	}
}

void Dacia::MemoryAllocationTracker::AddToHeap(ObjectContent objContent)
{

}

void Dacia::MemoryAllocationTracker::AddToHeap(uint32 id,
											   GPUObjectType type, 
											   int64 size, 
											   std::string path, 
											   void * extraData)
{
	if (m_heapContent.count(id))
	{
		Log::Print(LOG::LOG_WARNING, "An object with the same id (%d) already exists!", id);
		return;
	}

	m_heapContent.insert(std::make_pair(id, ObjectContent{id,0,type,size,path,(char*)extraData}));
}

void Dacia::MemoryAllocationTracker::RemoveFromHeap(uint32 id)
{

}

void Dacia::MemoryAllocationTracker::SignalObjectCreation(GPUObjectType, int64 size, void * extraData)
{
}

void Dacia::MemoryAllocationTracker::SignalObjectDeath(uint32 id)
{
}

void Dacia::MemoryAllocationTracker::RegisterObject(ObjectContent objContent)
{
}

void Dacia::MemoryAllocationTracker::UnregisterObject(uint32 id)
{
}

bool Dacia::MemoryAllocationTracker::IsUsed(uint32 id)
{
	std::unordered_map<uint32, ObjectContent>::iterator object;

	if ((object = m_heapContent.find(id)) == m_heapContent.end())
		return false;

	if (object->second.references)
		return true;

	return false;
}

bool Dacia::MemoryAllocationTracker::IsEmpty()
{
	return m_heapContent.empty();
}

void Dacia::MemoryAllocationTracker::OnCleanUp()
{
	if (!IsEmpty())
	{
		Log::Print(LOG::LOG_MAJOR, "There are %u objects that haven't been cleaned up \
                   properly from the video memory!");

		for (auto key : m_heapContent)
		{
			//key.second.logInfo();
		}

		throw HeapLeaking("Objects haven't been cleaned-up properly");
	}
}

Dacia::MemoryAllocationTracker::ObjectStillInUse::ObjectStillInUse(const char * message):
	std::runtime_error(message)
{
}

Dacia::MemoryAllocationTracker::ObjectStillInUse::ObjectStillInUse(std::string const & message) :
	std::runtime_error(message)
{
}

Dacia::MemoryAllocationTracker::HeapLeaking::HeapLeaking(const char * message):
	std::runtime_error(message)
{
}

Dacia::MemoryAllocationTracker::HeapLeaking::HeapLeaking(std::string const & message):
	std::runtime_error(message)
{
}

std::string Dacia::ObjectContent::LogInfo()
{
	static auto GetType = [](GPUObjectType ot) -> std::string
	{
		switch (ot)
		{
				case GPUObjectType::VERTEX_BUFFER:		return "Vertex Buffer Object";
				case GPUObjectType::ARRAY_BUFFER:		return "Array Buffer Object";
				case GPUObjectType::INDEX_BUFFER:		return "Element Buffer Object";
				case GPUObjectType::TEXTURE1D:			return "1d Texture";
				case GPUObjectType::TEXTURE2D:			return "2d Texture";
				case GPUObjectType::TEXTURE3D:			return "3d Texture";
				case GPUObjectType::SHADER_STEP:		return "Shader";
				case GPUObjectType::SHADER_PROGRAM:		return "Shader Program";
				case GPUObjectType::FRAMEBUFFER:		return "Framebuffer Object";
				case GPUObjectType::UNKNOWN:
				default:								return "Unknown";
		}
	};

	std::string info = "TYPE: " + GetType(type) 
						+ "( id: " + std::to_string(id) + ")\n";
	info += "No. References: " + std::to_string(references) + "\n";
	info += "Size: " + (sizeInBytes > 0 ? std::to_string(sizeInBytes) : "unknown") 
			+ " bytes\n";
	info += "Resource path: " + (pathOnDisk.empty() ? "unknown" : pathOnDisk) + "\n";
	info += (char*)extraData;

	return info;
}
