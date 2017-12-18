#pragma once

#include <Utilities/Common.hpp>
#include "Driver.hpp"


namespace Dacia
{
	namespace Graphics
	{
		enum class RenderMode :
			uint16
		{
			NO_DRAW,
			/*nothing should be drawn*/

			SCENE_2D = 1 << 1,
			/*scene contains 2d elements*/

			SCENE_3D = 1 << 2,
			/*scene contains 3d elements*/

			MIXED_2D_3D = SCENE_2D | SCENE_3D,
			/*scene contains both 2d and 3d*/

			FBO = 1 << 3,
			/*is rendered to a target*/

			HIGH_QUALITY = 1 << 4,
			/*should use highest quality*/

			DEPTH = 1 << 5,
			/*is depth buffer used*/

			STENCIL = 1 << 6,
			/*is stencil buffer used*/

			ALPHA = 1 << 8,
			/*is alpha used*/

			BLENDED = 1 << 10,
			/*is blend mode use*/

			CULL = 1 << 11,
			/*is anything culled*/

			TRACKED = 1 << 12
			/*should track gpu allocations*/
		};

		class RendererOptions;
		class Camera;
		class Scene;
		class SceneManager;

		typedef std::shared_ptr<Camera>			CameraPtr;
		typedef std::shared_ptr<Scene>			ScenePtr;
		typedef std::shared_ptr<SceneManager>	SceneManagerPtr;
		typedef std::shared_ptr<Driver>			DriverPtr;

		class Renderer final : 
			public Skeletons::Unique
		{
			public:

				Renderer();
				Renderer(RenderMode);
				Renderer(RendererOptions);
				~Renderer();

				void RegisterScene(ScenePtr);
				void UnregisterScene(ScenePtr);

				void SetCurrentScene(ScenePtr);
				void SetCurrentScene(uint32 id);

				ScenePtr GetCurrentScene();
				ScenePtr GetScene(std::string key);
				
				void RestoreDefaultScene();

				void LoadRenderingPipeline();
				void RestoreDefaultPipeline();

				void BeginScene3D();
				void EndScene3D();

				void BeginScene2D();
				void EndScene2D();

				void RenderScene();
				void Render2D();
				void Render3D();
				void RenderAll();

				void DrawOnScreen();
				void DrawToTarget(FramebufferPtr fbo);

				void SetShadingTechnique(ShaderPtr);
				void SetBlendFunction(BlendMode);

				void RenderToFile(std::string const & filename, bool createFile = true);
				void ApplySucessivePasses(FramebufferPtr fbo, uint32 noTimes);

				void ClearColor();
				void ClearBuffers();

				void SetPostProcessStage();

				void SetMaterial(Material &);
				void GetMaterial();

				std::pair<std::string, uint16> GetDriverVersion();

			protected:

				RenderMode									m_renderMode;
				SceneManagerPtr								m_sceneManager;
				
		};
	}
}

