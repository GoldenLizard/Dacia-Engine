#pragma once

#include <Utilities\EngineUtilities.hpp>

namespace Dacia
{
	class TextureManager;
	class ShaderManager;
	class ModelManager;

	class ResourceManager:
		public Skeletons::Unique
	{
		public:

			ResourceManager();
			~ResourceManager();

		private:
			
			//TextureManager m_textureManager;
			//ShaderManager  m_shaderManager;
			//ModelManager   m_modelManager;
			
	};
}

