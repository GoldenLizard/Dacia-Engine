#include "Renderer.hpp"

Dacia::Graphics::Renderer::RendererCleaner::RendererCleaner()
{
}

Dacia::Graphics::Renderer::RendererCleaner::~RendererCleaner()
{
}

Dacia::Graphics::DriverPtr 
Dacia::Graphics::Renderer::GetCurrentDriver()
{
	return m_currentDriver;
}
