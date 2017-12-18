#include "OpenGL_Utils.hpp"

std::stack<std::string> 
	Dacia::Graphics::OpenGL::GetErrors()
{
	int32 errorCode = -1;
	std::stack<std::string> errors;

	while ((errorCode = glGetError()) != GL_NO_ERROR)
		errors.push(ErrorTranslator(errorCode));

	return errors;
}

const std::string 
	Dacia::Graphics::OpenGL::ErrorTranslator(GLenum errorCode)
{
	switch (errorCode)
	{
		case GL_NO_ERROR:						return	"No error occured (GL_NO_ERROR)";
		case GL_INVALID_ENUM:					return	"Invalid value for a GLenum argument (GL_INVALID_ENUM)";
		case GL_INVALID_OPERATION:				return	"Invalid operation (GL_INVALID_OPERATION)";
		case GL_INVALID_FRAMEBUFFER_OPERATION:	return	"Framebuffer object is not complete (GL_INVALID_FRAMEBUFFER_OPERATION)";
		case GL_OUT_OF_MEMORY:					return  "No memory left (GL_OUT_OF_MEMORY)";
		case GL_STACK_UNDERFLOW:				return	"Stack underflow (GL_STACK_UNDERFLOW)";
		case GL_STACK_OVERFLOW:					return	"Stack overflow (GL_STACK_OVERFLOW)";
		case GL_TABLE_TOO_LARGE:				return  "Maximum number of objects allowed exceeded (GL_TABLE_TOO_LARGE)";

		default:
		{
			GLchar buffer[0xff] = "";
			sprintf_s(buffer, "Unknown OpenGL error code: %d", errorCode);
			return buffer;
		}
	}
}
