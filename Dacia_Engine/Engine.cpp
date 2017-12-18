#include "Engine.hpp"

Dacia::Engine::Engine()
{
}

Dacia::Engine::~Engine()
{
}

const std::shared_ptr<Dacia::Graphics::Driver> Dacia::Engine::GetCurrentDriver()
{
	return this->m_Renderer->GetCurrentDriver();
}

const std::shared_ptr<Dacia::MemoryAllocationTracker> Dacia::Engine::GetMemoryTracker()
{
	return this->m_MemoryTracker;
}
