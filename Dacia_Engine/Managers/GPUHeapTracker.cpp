#include "GPUHeapTracker.hpp"

Dacia::Graphics::GPUHeapTracker::GPUHeapTracker()
{
}

Dacia::Graphics::GPUHeapTracker::GPUHeapTracker(DriverOptions)
{
}

void Dacia::Graphics::GPUHeapTracker::EventLoop()
{
	auto events = DaciaEngine()->GetCurrentDriver()->GetEventQueue();
	
	for(auto driverEvent = events.front();
		!events.empty(); driverEvent = events.front(),
		events.pop())
	{
		driverEvent->LogEvent();
		driverEvent->Resolve();
	}
}

void Dacia::Graphics::GPUHeapTracker::RegisterObject(GPUHandle objectHandle)
{
}

void Dacia::Graphics::GPUHeapTracker::AddToHeap(uint32 id)
{
}

void Dacia::Graphics::GPUHeapTracker::AddToHeap(GPUHandle objectHandle)
{
}

void Dacia::Graphics::GPUHeapTracker::RemoveFromHeap(GPUHandle objectHandle)
{
}

void Dacia::Graphics::GPUHeapTracker::RemoveFromHeap(uint32 id)
{
}

bool Dacia::Graphics::GPUHeapTracker::Exists(uint32 objectID)
{
	return false;
}

//void Dacia::Graphics::GPUHeapTracker::ReceiveEvent(DriverEvent)
//{
//}

void Dacia::Graphics::GPUHeapTracker::IncreaseReference(uint32 id)
{
}

void Dacia::Graphics::GPUHeapTracker::DecreaseReference(uint32 id)
{
}

void Dacia::Graphics::GPUHeapTracker::OnObjectDeath(uint32 objectID)
{
}

void Dacia::Graphics::GPUHeapTracker::OnObjectCreation(uint32 objectID)
{
}
