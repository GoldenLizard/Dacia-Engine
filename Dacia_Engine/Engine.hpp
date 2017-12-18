#pragma once

#include <Graphics\Renderer.hpp>
#include <Managers\ResourceManager.hpp>
#include <Managers\MemoryAllocationTracker.hpp>

namespace Dacia
{
	class Engine final : 
		public Skeletons::Unique
	{
		static std::unique_ptr<Engine> daciaEngine;

		public:

			static void InitEngine();

			~Engine();

			static const std::shared_ptr<Graphics::Driver>			GetCurrentDriver();
			static const std::shared_ptr<MemoryAllocationTracker>	GetMemoryTracker();

			static void SwitchDriver(Graphics::DriverType newDriverType);


		private:

			Engine();

			std::shared_ptr<ResourceManager>			m_ResourceManager;
			std::shared_ptr<MemoryAllocationTracker>	m_MemoryTracker;
			std::shared_ptr<Graphics::Renderer>			m_Renderer;


	};
}

