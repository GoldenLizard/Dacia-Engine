#include "Engine.hpp"

std::unique_ptr<Dacia::Engine> Dacia::Engine::daciaEngine = nullptr;

void Dacia::Engine::InitEngine()
{
}

Dacia::Engine::~Engine()
{
}

const std::shared_ptr<Dacia::Graphics::Driver> Dacia::Engine::GetCurrentDriver()
{
	//return daciaEngine->m_Renderer->GetCurrentDriver();
	return nullptr;
}

const std::shared_ptr<Dacia::MemoryAllocationTracker> Dacia::Engine::GetMemoryTracker()
{
	return daciaEngine->m_MemoryTracker;
}
