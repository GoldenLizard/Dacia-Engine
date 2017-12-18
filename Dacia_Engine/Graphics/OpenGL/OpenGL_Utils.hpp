#pragma once

#include <stack>
#include <Utilities\EngineUtilities.hpp>
#include "OpenGL_Strings.hpp"

#define OPENGL_CALL(func,...)				\
{											\
	func(__VA_ARGS__);						\
	Dacia::Graphics::OpenGL::GetErrors();	\
}											\

namespace Dacia
{
	namespace Graphics
	{
		namespace OpenGL
		{
			enum class OpenGLVersion : byte
			{
				OPENGL_20, OPENGL_21,
				OPENGL_30, OPENGL_31, OPENGL_32, OPENGL_33,
				OPENGL_40, OPENGL_41, OPENGL_42, OPENGL_43,
				OPENGL_44, OPENGL_45, OPENGL_46
			};

			std::unordered_map<OpenGLVersion, std::string> 
				const k_versionStrings =
			{
				{ OpenGLVersion::OPENGL_20,	v_OpenGL20 } ,
				{ OpenGLVersion::OPENGL_21,	v_OpenGL21 } ,
				{ OpenGLVersion::OPENGL_30,	v_OpenGL30 } ,
				{ OpenGLVersion::OPENGL_31,	v_OpenGL31 } ,
				{ OpenGLVersion::OPENGL_32,	v_OpenGL32 } ,
				{ OpenGLVersion::OPENGL_33,	v_OpenGL33 } ,
				{ OpenGLVersion::OPENGL_40,	v_OpenGL40 } ,
				{ OpenGLVersion::OPENGL_41,	v_OpenGL41 } ,
				{ OpenGLVersion::OPENGL_42,	v_OpenGL42 } ,
				{ OpenGLVersion::OPENGL_43,	v_OpenGL43 } ,
				{ OpenGLVersion::OPENGL_44,	v_OpenGL44 } ,
				{ OpenGLVersion::OPENGL_45,	v_OpenGL45 } ,
				{ OpenGLVersion::OPENGL_46,	v_OpenGL46 }
			};

			std::stack<std::string> GetErrors();
			const std::string ErrorTranslator(GLenum errorCode);
		}
	}
}