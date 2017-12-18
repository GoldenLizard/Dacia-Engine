#pragma once
#include <Graphics/Shader.hpp>
#include "OpenGL_Utils.hpp"

namespace Dacia
{
	namespace Graphics
	{
		namespace OpenGL
		{
			class ShaderImplOpenGL :
				public ShaderImpl
			{
				uint32 UseDefault(GLenum type);

			public:

				ShaderImplOpenGL();

				uint32 Compile(GLenum type, std::string const & source);

				virtual uint32	CompileShader(std::string vertex,
					std::string fragment) override;

				virtual uint32	CompileShader(std::string vertex,
					std::string fragment,
					std::string geometry,
					std::string tessellation,
					std::string control)	override;

				virtual uint32	CompileShader(std::string vertex,
					std::string fragment,
					std::string tessellation,
					std::string control)	override;

				virtual uint32	CompileShader(std::string vertex,
					std::string fragment,
					std::string optionalShader,
					ShaderType)					override;

				virtual std::string GetDefaultShader(ShaderType) override;

				virtual void	    GetError()		override;
				virtual void		UseShader()		override;

				virtual void		RegisterShader()		override;
				virtual void		UnregisterShader()		override;
				virtual void		CleanUp()				override;

				virtual uint64		GetProgramSizeInBytes() override;

				void AddFlag(ShaderType, std::string flagName, std::string & shaderSource) override;
				void SetVersion(byte versionID, std::string & shaderSource) override;

				std::string GetShaderBinaryData(bool getBinary = false, const uint32 maxSize = 4096);

#pragma region("uniforms")
				virtual void SetBool(std::string name, bool val) override;
				virtual void SetInt(std::string name, const int32 & val) override;
				virtual void SetDouble(std::string name, const double & val) override;
				virtual void SetFloat(std::string name, const float & val) override;
				virtual void SetUint(std::string name, const uint32 & val) override;

				virtual void SetVec2i(std::string name, int32 x, int32 y) override;
				virtual void SetVec2i(std::string name, std::array<int32, 2> vec2) override;
				virtual void SetVec2i(std::string name, int32 vec2[2]) override;
				virtual void SetVec2i(std::string name, glm::i32vec2 vec2) override;

				virtual void SetVec2u(std::string name, uint32 x, uint32 y) override;
				virtual void SetVec2u(std::string name, std::array<uint32, 2> vec2) override;
				virtual void SetVec2u(std::string name, uint32 vec2[2]) override;
				virtual void SetVec2u(std::string name, glm::u32vec2 vec2) override;

				virtual void SetVec2f(std::string name, float x, float y) override;
				virtual void SetVec2f(std::string name, std::array<float, 2> vec2) override;
				virtual void SetVec2f(std::string name, float vec2[2]) override;
				virtual void SetVec2f(std::string name, glm::vec2 vec2) override;

				virtual void SetVec3i(std::string name, int32 x, int32 y, int32 z) override;
				virtual void SetVec3i(std::string name, std::array<int32, 3> vec3) override;
				virtual void SetVec3i(std::string name, int32 vec3[3]) override;
				virtual void SetVec3i(std::string name, glm::i32vec3 vec3) override;

				virtual void SetVec3u(std::string name, uint32 x, uint32 y, uint32 z) override;
				virtual void SetVec3u(std::string name, std::array<uint32, 3> vec3) override;
				virtual void SetVec3u(std::string name, uint32 vec3[3]) override;
				virtual void SetVec3u(std::string name, glm::u32vec2 vec3) override;

				virtual void SetVec3f(std::string name, float x, float y, float z) override;
				virtual void SetVec3f(std::string name, std::array<float, 3> vec3) override;
				virtual void SetVec3f(std::string name, float vec3[3]) override;
				virtual void SetVec3f(std::string name, glm::u32vec2 vec3) override;

				virtual void SetVec4i(std::string name, int32 x, int32 y, int32 z, int32 w) override;
				virtual void SetVec4i(std::string name, std::array<int32, 4> vec4) override;
				virtual void SetVec4i(std::string name, int32 vec4[4]) override;
				virtual void SetVec4i(std::string name, glm::i32vec4 vec4) override;

				virtual void SetVec4u(std::string name, uint32 x, uint32 y, uint32 z, uint32 w) override;
				virtual void SetVec4u(std::string name, std::array<uint32, 3> vec4) override;
				virtual void SetVec4u(std::string name, uint32 vec4[3]) override;
				virtual void SetVec4u(std::string name, glm::u32vec2 vec4) override;

				virtual void SetVec4f(std::string name, float x, float y, float z, float w) override;
				virtual void SetVec4f(std::string name, std::array<float, 3> vec4) override;
				virtual void SetVec4f(std::string name, float vec4[4]) override;
				virtual void SetVec4f(std::string name, glm::vec4 vec4) override;

				virtual void SetMat2x2f(std::string name, std::array<float, 4>) override;
				virtual void SetMat2x2f(std::string name, float mat2x2[4]) override;
				virtual void SetMat2x2f(std::string name, float mat2x2[2][2]) override;
				virtual void SetMat2x2f(std::string name, glm::mat2 const & mat2x2) override;

				virtual void SetMat3x3f(std::string name, std::array<float, 9>) override;
				virtual void SetMat3x3f(std::string name, float mat3x3[9]) override;
				virtual void SetMat3x3f(std::string name, float mat3x3[3][3]) override;
				virtual void SetMat3x3f(std::string name, glm::mat3 const & mat3x3) override;

				virtual void SetMat4x4f(std::string name, std::array<float, 16>) override;
				virtual void SetMat4x4f(std::string name, float mat4x4[16]) override;
				virtual void SetMat4x4f(std::string name, float mat4x4[4][4]) override;
				virtual void SetMat4x4f(std::string name, glm::mat4 const & mat4x4) override;

				virtual void SetSampler1d(std::string name, uint32 id) override;
				virtual void SetSampler2d(std::string name, uint32 id) override;
				virtual void SetSampler3d(std::string name, uint32 id) override;

				virtual void SetCubemap(std::string name, uint32 id) override;

			};
#pragma endregion


		}
	}
}