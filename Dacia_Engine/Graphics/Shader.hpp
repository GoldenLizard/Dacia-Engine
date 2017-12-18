#pragma once

#include <unordered_set>
#include <queue>

#include <Engine.hpp>
#include "Driver.hpp"

namespace Dacia
{
	namespace Graphics
	{
		constexpr uint32 INVALID_SHADER = 0x00;

		enum class UniformType : byte
		{
			INT,		UINT,
			BOOL,		FLOAT,		DOUBLE,		//PODs
			VEC2I,		VEC2U,		VEC2F,		//vec of 2 elements
			VEC3I,		VEC3U,		VEC3F,		//vec of 3 elements
			VEC4I,		VEC4U,		VEC4F,		//vec of 4 elements
			MAT2X2I,	MAT2X2U,	MAT2X2F,	//2x2 matrix
			MAT3X3I,	MAT3X3U,	MAT3X3F,	//3x3 matrix
			MAT4X4I,	MAT4X4U,	MAT4X4F,	//4x4 matrix
			SAMPLER1D,	SAMPLER2D,	SAMPLER3D,	//texture samplers
			CUBEMAP
		};

		enum class ShaderType 
			: byte
		{
			VERTEX,
			FRAGMENT,
			GEOMETRY,
			TESSELLATION_CONTROL,
			TESSELLATION_EVALUATION
		};

		struct FailedLinkage :
			public std::runtime_error
		{
			explicit FailedLinkage(const std::string & _Message) :
				std::runtime_error(_Message.c_str())
			{}

			explicit FailedLinkage(const char * _Message) :
				std::runtime_error(_Message)
			{}
		};

		struct FailedCompilation :
			public std::runtime_error
		{
			explicit FailedCompilation(const std::string & _Message) :
				std::runtime_error(_Message.c_str())
			{}

			explicit FailedCompilation(const char * _Message) :
				std::runtime_error(_Message)
			{}
		};


		class ShaderImpl : 
			Skeletons::Noncopyable
		{
			protected:

				std::unordered_map<std::string, uint32>	m_uniforms;

				bool			m_isCompiled{ false };
				std::string		m_binaryData;
				size_t			m_sizeInBytes;

			public:

				virtual uint32	CompileShader(std::string vertex,
											  std::string fragment,
											  std::string geometry,
											  std::string tessellation,
											  std::string control) = 0;

				virtual uint32	CompileShader(std::string vertex,
											  std::string fragment,
											  std::string tessellation,
											  std::string control) = 0;

				virtual uint32	CompileShader(std::string vertex,
											  std::string fragment,
											  std::string optionalShader,
											  ShaderType = ShaderType::GEOMETRY) = 0;

				virtual uint32	CompileShader(std::string vertex,
											  std::string fragment)		= 0;

				virtual void		GetError()			= 0;
				virtual void		UseShader()			= 0;
				virtual void		RegisterShader()	= 0;
				virtual void		UnregisterShader()  = 0;
				virtual void		CleanUp()			= 0;

				virtual uint64		GetProgramSizeInBytes() = 0;

				void PrintErrors();

				virtual std::string GetDefaultShader(ShaderType) = 0;

				virtual void AddFlag(ShaderType, std::string flagName, std::string & shaderSource) = 0;
				virtual void SetVersion(byte versionID, std::string & shaderSource)	= 0;

				inline uint32 const GetHandle() const
				{
					return m_shaderHandle.handle;
				}

#pragma region("uniforms")

				virtual void SetBool(std::string name, bool val) = 0;
				virtual void SetInt(std::string name, const int32 & val)		= 0;
				virtual void SetDouble(std::string name, const double & val)	= 0;
				virtual void SetFloat(std::string name, const float & val)		= 0;
				virtual void SetUint(std::string name, const uint32 & val)		= 0;

				virtual void SetVec2i(std::string name, int32 x, int32 y)			= 0;
				virtual void SetVec2i(std::string name, std::array<int32,2> vec2)	= 0;
				virtual void SetVec2i(std::string name, int32 vec2[2])				= 0;
				virtual void SetVec2i(std::string name, glm::i32vec2 vec2)			= 0;
	
				virtual void SetVec2u(std::string name, uint32 x, uint32 y)			= 0;
				virtual void SetVec2u(std::string name, std::array<uint32, 2> vec2)	= 0;
				virtual void SetVec2u(std::string name, uint32 vec2[2])				= 0;
				virtual void SetVec2u(std::string name, glm::u32vec2 vec2)			= 0;

				virtual void SetVec2f(std::string name, float x, float y)			= 0;
				virtual void SetVec2f(std::string name, std::array<float, 2> vec2)	= 0;
				virtual void SetVec2f(std::string name, float vec2[2])				= 0;
				virtual void SetVec2f(std::string name, glm::vec2 vec2)				= 0;

				virtual void SetVec3i(std::string name, int32 x, int32 y, int32 z)	= 0;
				virtual void SetVec3i(std::string name, std::array<int32, 3> vec3)	= 0;
				virtual void SetVec3i(std::string name, int32 vec3[3])				= 0;
				virtual void SetVec3i(std::string name, glm::i32vec3 vec3)			= 0;

				virtual void SetVec3u(std::string name, uint32 x, uint32 y, uint32 z) = 0;
				virtual void SetVec3u(std::string name, std::array<uint32, 3> vec3)	= 0;
				virtual void SetVec3u(std::string name, uint32 vec3[3])				= 0;
				virtual void SetVec3u(std::string name, glm::u32vec2 vec3)			= 0;

				virtual void SetVec3f(std::string name, float x, float y, float z)	= 0;
				virtual void SetVec3f(std::string name, std::array<float, 3> vec3)	= 0;
				virtual void SetVec3f(std::string name, float vec3[3])				= 0;
				virtual void SetVec3f(std::string name, glm::u32vec2 vec3)			= 0;

				virtual void SetVec4i(std::string name, int32 x, int32 y, int32 z, int32 w)	= 0;
				virtual void SetVec4i(std::string name, std::array<int32, 4> vec4)			= 0;
				virtual void SetVec4i(std::string name, int32 vec4[4])						= 0;
				virtual void SetVec4i(std::string name, glm::i32vec4 vec4)					= 0;

				virtual void SetVec4u(std::string name, uint32 x, uint32 y, uint32 z, uint32 w) = 0;
				virtual void SetVec4u(std::string name, std::array<uint32, 3> vec4)			  = 0;
				virtual void SetVec4u(std::string name, uint32 vec4[3])						  = 0;
				virtual void SetVec4u(std::string name, glm::u32vec2 vec4)					  = 0;

				virtual void SetVec4f(std::string name, float x, float y, float z, float w)	= 0;
				virtual void SetVec4f(std::string name, std::array<float, 3> vec4)			= 0;
				virtual void SetVec4f(std::string name, float vec4[4])						= 0;
				virtual void SetVec4f(std::string name, glm::vec4 vec4)						= 0;

				virtual void SetMat2x2f(std::string name, std::array<float, 4>) = 0;
				virtual void SetMat2x2f(std::string name, float mat2x2[4]) = 0;
				virtual void SetMat2x2f(std::string name, float mat2x2[2][2]) = 0;
				virtual void SetMat2x2f(std::string name, glm::mat2 const & mat2x2) = 0;

				virtual void SetMat3x3f(std::string name, std::array<float, 9>) = 0;
				virtual void SetMat3x3f(std::string name, float mat3x3[9]) = 0;
				virtual void SetMat3x3f(std::string name, float mat3x3[3][3]) = 0;
				virtual void SetMat3x3f(std::string name, glm::mat3 const & mat3x3) = 0;

				virtual void SetMat4x4f(std::string name, std::array<float, 16>) = 0;
				virtual void SetMat4x4f(std::string name, float mat4x4[16]) = 0;
				virtual void SetMat4x4f(std::string name, float mat4x4[4][4]) = 0;
				virtual void SetMat4x4f(std::string name, glm::mat4 const & mat4x4) = 0;

				virtual void SetSampler1d(std::string name, uint32 id) = 0;
				virtual void SetSampler2d(std::string name, uint32 id) = 0;
				virtual void SetSampler3d(std::string name, uint32 id) = 0;

				virtual void SetCubemap(std::string name, uint32 id) = 0;
#pragma endregion
			protected:

				GPU_Handle				m_shaderHandle;
				std::queue<std::string> m_errors;
		};


		class Shader : 
			public Skeletons::Noncopyable
		{
			public:

				Shader();
				
				Shader(std::string const & vertex, 
					   std::string const & fragment, 
					   std::string const & geometry);

				Shader(	const char * vertex,
						const char * fragment,
						const char * geometry);

				Shader(	std::string const & vertex,
						std::string const & fragment,
						std::string const & geometry,
						std::string const & tessellation);

				Shader(	const char * vertex,
						const char * fragment,
						const char * geometry,
						const char * tessellation);

				Shader(std::string const & vertex,
					   std::string const & fragment);

				Shader(	const char * vertex,
						const char * fragment);

			   ~Shader();

			   void operator()();
			   
			   void UseShader();
			   void CleanUp();
			   void Init();

			   bool IsPipelinePart();
			   
			   static bool IsShaderSupported(ShaderType type);
			   static bool IsPipelineSupported();

			   template<typename T>
			   void SetParamater(std::string name, UniformType uniform, T value);

			   void SetShader(ShaderType, std::string const & source);
			   void AddFlag(ShaderType, std::string const & flag);

			   uint32 CompileShader();

			private:

				void SetDriverImplementation();
				void ApplyFlags();
				void SetVersion();

				uint32 const GetHandle() const;

				static std::string ReadShader(std::string const & source);
				
				template<size_t size>
				static std::string ReadShader(char (&src)[size]);

				template<size_t size>
				static std::string ReadShader(wchar_t (&src)[size]);

				bool m_isCompiled{false};

				std::string m_vertex;
				std::string m_fragment;
				std::string m_geometry;
				std::string m_tessellation;
				std::string m_control;

				std::unordered_map<ShaderType, std::vector<std::string>>				m_flags;
				ShaderImplPtr													m_shaderImpl;
		};

	}

}