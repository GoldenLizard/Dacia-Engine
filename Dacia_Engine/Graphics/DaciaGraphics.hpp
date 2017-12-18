#pragma once
#include <memory>
#include <Utilities\EngineUtilities.hpp>

namespace Dacia
{
	enum class GPUObjectType : byte
	{
		VERTEX_BUFFER,
		ARRAY_BUFFER,
		INDEX_BUFFER,
		TEXTURE1D,
		TEXTURE2D,
		TEXTURE3D,
		CUBEMAP,
		SHADER_STEP,
		SHADER_PROGRAM,
		FRAMEBUFFER,
		UNKNOWN
	};

	namespace Graphics
	{
		class Shader;
		class ShaderImpl;
		class Texture;
		class TextureImpl;
		class Framebuffer;
		class FramebufferImpl;
		class Mesh;
		class MeshImpl;
		class Sprite;
		class SpriteImpl;
		class Material;
		class MultiMaterial;
		class Cubemap;
		class CubemapImpl;


		struct GPU_Handle
		{
			GPUObjectType	type;
			uint32			handle;
			uint32			id;
			uint32			references;
			int64			sizeInBytes;

			uint32 inline operator()()
			{
				return handle;
			}

			bool IsAvailable();

			void SignalCreation();
			void SignalDeath();

		private:

			bool m_isAlive;
		};

		typedef std::shared_ptr<Shader>					ShaderPtr;
		typedef std::shared_ptr<Texture>				TexturePtr;
		typedef std::shared_ptr<Framebuffer>			FramebufferPtr;
		typedef std::shared_ptr<Mesh>					MeshPtr;
		typedef std::shared_ptr<Sprite>					SpritePtr;
		typedef std::shared_ptr<ShaderImpl>				ShaderImplPtr;
		typedef std::shared_ptr<TextureImpl>			TextureImplPtr;
		typedef std::shared_ptr<FramebufferImpl>		FramebufferImplPtr;
		typedef std::shared_ptr<MeshImpl>				MeshImplPtr;
		typedef std::shared_ptr<SpriteImpl>				SpriteImplPtr;

		typedef std::shared_ptr<GPU_Handle>				GPUHandlePtr;

	}
}