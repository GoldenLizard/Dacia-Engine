#pragma once
#include <Utilities\Common.hpp>

namespace Dacia
{
	namespace Graphics
	{
		namespace OpenGL
		{
			constexpr char * versionDirective	= "#version";
			constexpr char * core				= "#core";
			
			std::string inline const 
				GetVersionDirective(byte minor, byte major)
			{
				return std::string("#version" + 
									char(0x20) + 
									minor + 
									major + 
									std::string(core));
			}

			constexpr char * v_OpenGL20 = "#version 110 core";
			constexpr char * v_OpenGL21 = "#version 120 core";
			constexpr char * v_OpenGL30 = "#version 130 core";
			constexpr char * v_OpenGL31 = "#version 140 core";
			constexpr char * v_OpenGL32 = "#version 150 core";
			constexpr char * v_OpenGL33 = "#version 330 core";
			constexpr char * v_OpenGL40 = "#version 400 core";
			constexpr char * v_OpenGL41 = "#version 410 core";
			constexpr char * v_OpenGL42 = "#version 420 core";
			constexpr char * v_OpenGL43 = "#version 430 core";
			constexpr char * v_OpenGL44 = "#version 440 core";
			constexpr char * v_OpenGL45 = "#version 450 core";
			constexpr char * v_OpenGL46 = "#version 460 core";

			constexpr char* ERROR_STR[] =
			{
				"GL_NO_ERROR",
				"GL_INVALID_ENUM",
				"GL_INVALID_OPERATION",
				"GL_INVALID_FRAMEBUFFER_OPERATION",
				"GL_OUT_OF_MEMORY",
				"GL_STACK_UNDERFLOW",
				"GL_STACK_OVERFLOW",
			};

			std::string const k_defaultVertexShaderVersion3Plus =
			"\
		    layout (location = 0) in vec2 XY;\
		    layout (location = 1) in vec2 UV;\
		    out vec2 xy;\
		    out vec2 uv;\
		    void main(){xy = XY;uv = UV;})";

			std::string const k_defaultFragmentShaderVersion3Plus =
			"\
			in vec2 xy;\
			in vec2 uv;\
			out vec4 FragColor;\
			void main(){FragColor=vec4(uv,xy.x+xy.y,1.0);})";


			std::string const k_defaultVertexShaderVersion2 =
			"\
		    attribute in vec2 XY;\
		    attribute in vec2 UV;\
		    varying out vec2 xy;\
		    varying out vec2 uv;\
		    void main(){xy = XY;uv = UV;})";

			std::string const k_defaultFragmentShaderVersion2 =
			R"(
			varying in vec2 xy;
			varying in vec2 uv;
			void main(){_glFragColor=vec4(uv,xy.x+xy.y,1.0);})";

		}
	}
}