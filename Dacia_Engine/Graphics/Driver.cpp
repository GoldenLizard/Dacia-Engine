#include "Driver.hpp"

Dacia::Graphics::Driver::Driver(DriverOptions options)
{
}

Dacia::Graphics::Driver::~Driver()
{
}

void Dacia::Graphics::Driver::RenderAll()
{
	//DriverImpl->RenderAll();
}

void Dacia::Graphics::Driver::Render2D(SpritePtr)
{
}

void Dacia::Graphics::Driver::Render3D(MeshPtr)
{
}

void Dacia::Graphics::Driver::RestoreDefaultFramebuffer()
{
}

void Dacia::Graphics::Driver::RenderToTarget(FramebufferPtr)
{
	
}

inline bool Dacia::Graphics::Resolution::IsMax()
{
	return false;
}

std::pair<Dacia::Graphics::DriverType, Dacia::byte> 
	Dacia::Graphics::Driver::GetCurrentVersion()
{
	return m_driverImpl->GetVersion();
}

std::pair<Dacia::Graphics::DriverType, Dacia::byte> 
Dacia::Graphics::DriverImpl::GetVersion()
{
	return m_driverVersion;
}

std::queue<Dacia::Graphics::DriverEvent*> 
Dacia::Graphics::Driver::GetEventQueue()
{
	return m_events;
}
