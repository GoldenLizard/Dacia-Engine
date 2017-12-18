#pragma once

#include <Utilities/Common.hpp>
#include <Utilities/EngineUtilities.hpp>
#include <Graphics/DaciaGraphics.hpp>
#include <Dacia.Math\Color\Colors.hpp>
#include <queue>

namespace Dacia
{
	namespace Graphics
	{
		enum class ShaderTypes;
		class DriverImpl;
		class Scene3D;

		enum class DriverType 
			: byte
		{
			DRUNK,
			OPENGL,			
			OPENGLES,
			VULKAN,
			DIRECTX
		};

		enum class CoordinateSystem 
			: byte
		{ LEFT_HAND, 
		  RIGHT_HAND };


		enum class GPUBufferType
		{
			NONE,
			COLOR	= 1 << 1,
			STENCIL = 1 << 2,
			DEPTH	= 1 << 3,
			ALL		= COLOR | STENCIL | DEPTH
		};

		enum class BlendMode
		{
			NONE,
			FULL,
			LESS_DST,
			MORE_DST,
			LESS_SRC,
			MORE_SRC,
			CONSTANT,
			EQUAL,
			REVERSE_SRC,
			REVERSE_DST,
			COLOR_SRC,
			COLOR_DST,
			BRIGHTNESS,
			CUSTOM
		};

		struct DriverOptions
		{
			DriverOptions() = default;

			DriverType		 driverType;
			CoordinateSystem coordSystem;
			byte			 driverVersion;
			bool			 enableGPUTracking;
			ShaderTypes		 supportedShaders;
			GPUBufferType	 supportedBuffers;
		};


		struct DriverEvent
		{
			virtual void LogEvent()		= 0;
			virtual void Resolve()		= 0;
		};

		struct Resolution
		{
			union { uint32 x, width;  };
			union { uint32 y, height; };

			bool inline IsMax();

			inline constexpr operator dmath::Vector2() const
			{
				return dmath::Vector2(x,y);
			}

			inline constexpr operator std::pair<uint32, uint32>() const
			{
				return std::make_pair(x,y);
			}

			inline constexpr bool operator==(Resolution other) const
			{
				return  x == other.x &&
						y == other.y;
			}

			inline constexpr bool operator==(dmath::Vector2 other) const
			{
				return  x == other.x &&
						y == other.y;
			}

			inline constexpr bool operator==(std::pair<uint32,uint32> other) const
			{
				return  x == other.first &&
						y == other.second;
			}
		};

		typedef std::shared_ptr<DriverImpl> DriverImplPtr;
		typedef dmath::color::Color Color;

		class DriverImpl
		{
			protected:
				
				DriverType					m_driverType;
				std::pair<DriverType, byte>	m_driverVersion;
				GPUBufferType				m_buffersUsed;
				Color						m_currentClearColor;
				ShaderTypes					m_supportedShaders;
				BlendMode					m_currentBlendMode;

			public:

				DriverImpl();
				virtual ~DriverImpl();

				virtual void BeginScene3D() = 0;
				virtual void EndScene3D()	= 0;

				virtual void Render2D()	= 0;
				virtual void Render3D()	= 0;

				virtual void ClearBuffers() = 0;
				virtual void ClearColor();

				std::pair<DriverType, byte> GetVersion();

				virtual void BindDefaultFramebuffer() = 0;
				virtual void BindFramebuffer(FramebufferPtr) = 0;
		};

		class Driver : 
			public Skeletons::Unique
		{
			public:

				Driver(DriverOptions options);
				~Driver();

				void RenderAll();
				void Render2D(SpritePtr);
				void Render3D(MeshPtr);

				void RestoreDefaultFramebuffer();
				void RenderToTarget(FramebufferPtr);

				void SetClearColor(Color);
				void SetBuffersToClear(GPUBufferType);

				void ClearColor();
				void ClearColor(Color c);
				void ClearBuffers(GPUBufferType buffers);

				std::string					ErrorTranslator(uint32 errorCode) ;
				std::pair<DriverType, byte> GetCurrentVersion() ;

				CoordinateSystem GetCoordinateSystem();

				bool VerifyObject(GPUHandlePtr);
				void BroadcastEvent(DriverEvent*);

				std::queue<DriverEvent*> GetEventQueue();

				void SetFullScreenViewport();
				void SetResolution(Resolution res);

				Resolution GetMaxResouliton();

				bool IsShaderSupported(ShaderTypes typeToCheck);

				std::string GetVendorName();
				std::string GetRendererName();
				std::string GetExtensions();

			private:

				std::queue<DriverEvent*> m_events;

				DriverImplPtr			m_driverImpl;
				FramebufferImplPtr		m_currentRenderTarget;
		};
	}
}