#pragma once

#include <Graphics\Renderer.hpp>
#include <Managers\ResourceManager.hpp>
#include <Managers\MemoryAllocationTracker.hpp>

namespace Dacia
{
	enum class EngineHints:
		byte
	{

	};

	struct EngineOptions
	{
		 Graphics::DriverType m_driverType;
	};

	class Engine final : 
		public Skeletons::Unique
	{
		public:

			Engine();
		   ~Engine();

			const std::shared_ptr<Graphics::Driver>			GetCurrentDriver();
			const std::shared_ptr<MemoryAllocationTracker>	GetMemoryTracker();

			static void SwitchDriver(Graphics::DriverType newDriverType);

		private:

			std::shared_ptr<ResourceManager>			m_ResourceManager;
			std::shared_ptr<MemoryAllocationTracker>	m_MemoryTracker;
			std::shared_ptr<Graphics::Renderer>			m_Renderer;
	};

	inline Engine * DaciaEngine()
	{
		static Engine *_engine = new Engine;
		return _engine;
	}
}

