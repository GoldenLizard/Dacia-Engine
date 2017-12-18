

#include "Shader.hpp"

#include <fstream>
#include <sstream>

Dacia::Graphics::Shader::Shader()
{
}

Dacia::Graphics::Shader::Shader(std::string const & vertex, std::string const & fragment, std::string const & geometry):
	m_vertex(vertex),
	m_fragment(fragment),
	m_geometry(geometry)
{
}

Dacia::Graphics::Shader::Shader(const char * vertex, const char * fragment, const char * geometry):
	m_vertex(vertex),
	m_fragment(fragment),
	m_geometry(geometry)
{
}

Dacia::Graphics::Shader::Shader(std::string const & vertex, std::string const & fragment, std::string const & geometry, std::string const & tessellation):
	m_vertex(vertex),
	m_fragment(fragment),
	m_geometry(geometry),
	m_tessellation(tessellation)
{
}

Dacia::Graphics::Shader::Shader(const char * vertex, const char * fragment, const char * geometry, const char * tessellation):
	m_vertex(vertex),
	m_fragment(fragment),
	m_geometry(geometry),
	m_tessellation(tessellation)
{
}

Dacia::Graphics::Shader::Shader(std::string const & vertex, std::string const & fragment)
	:m_vertex(vertex),
	 m_fragment(fragment)
{
}

Dacia::Graphics::Shader::Shader(const char * vertex, const char * fragment):
	m_vertex(vertex),
	m_fragment(fragment)
{
}

Dacia::Graphics::Shader::~Shader()
{
}

void Dacia::Graphics::Shader::operator()()
{
	return m_shaderImpl->UseShader();
}

void Dacia::Graphics::Shader::UseShader()
{
	return m_shaderImpl->UseShader();
}

void Dacia::Graphics::Shader::SetShader(ShaderType shaderType, std::string const & source)
{
	if (!m_isCompiled)
	{
		switch (shaderType)
		{
			case ShaderType::VERTEX:						m_vertex		= source; return;
			case ShaderType::FRAGMENT:						m_fragment		= source; return;
			case ShaderType::GEOMETRY:						m_geometry		= source; return;
			case ShaderType::TESSELLATION_EVALUATION:		m_tessellation	= source; return;
			case ShaderType::TESSELLATION_CONTROL:			m_control		= source; return;

			default: Log::Print(LOG::LOG_WARNING, "Invalid shader type!"); return;
		}
	}
	else
	{
		Log::Print(LOG::LOG_WARNING, "Shader has already been compiled!");
	}
}

void Dacia::Graphics::Shader::ApplyFlags()
{
	std::string * src = nullptr;
	bool skip = false;

	for (auto & shaderType : m_flags)
	{
		skip = false;
		switch (shaderType.first)
		{
			case ShaderType::VERTEX:						src = &m_vertex; break;
			case ShaderType::FRAGMENT:						src = &m_fragment; break;
			case ShaderType::GEOMETRY:						src = &m_geometry; break;
			case ShaderType::TESSELLATION_EVALUATION:		src = &m_tessellation; break;
			case ShaderType::TESSELLATION_CONTROL:			src = &m_control; break;

			default: 
			{
				Log::Print(LOG::LOG_WARNING, "Invalid shader type!");
				skip = true;
			}
		}

		if (skip) continue;

		for (auto & flag : shaderType.second)
		{
			return m_shaderImpl->AddFlag(shaderType.first, flag, *src);
		}
	}	
}

void Dacia::Graphics::Shader::SetVersion()
{
	for (std::string * shader : { &m_vertex,
								  &m_geometry,
								  &m_fragment,
								  &m_tessellation,
								  &m_control })

		if (!shader->empty())
			m_shaderImpl->SetVersion(Engine::GetCurrentDriver()->GetCurrentVersion().second, *shader);
}

void Dacia::Graphics::Shader::SetDriverImplementation()
{
	//m_shaderImpl = Engine::GetCurrentDriver()->GetShaderImplementation();
}

Dacia::uint32 const Dacia::Graphics::Shader::GetHandle() const
{
	return m_shaderImpl->GetHandle();
}

void Dacia::Graphics::Shader::AddFlag(ShaderType sType, std::string const & flag)
{
	std::function<std::string&(ShaderType)> helper 
		= [this](ShaderType sType) -> std::string&
	{
		switch (sType)
		{
			case ShaderType::VERTEX:
				return m_vertex;

			case ShaderType::FRAGMENT:
				return m_fragment;

			case ShaderType::GEOMETRY:
				return m_geometry;

			case ShaderType::TESSELLATION_CONTROL:
				return m_control;

			case ShaderType::TESSELLATION_EVALUATION:
				return m_tessellation;		
		}
	};

	return m_shaderImpl->AddFlag(sType, flag, helper(sType));
}

Dacia::uint32 Dacia::Graphics::Shader::CompileShader()
{
	if (!m_isCompiled)
	{
		ApplyFlags();
		SetVersion();

		return m_shaderImpl->CompileShader(m_vertex,
										   m_fragment,
										   m_geometry,
										   m_tessellation,
										   m_control);
	}

	else
		Log::Print(LOG::LOG_WARNING, "Shader has already been compiled!");

	return INVALID_SHADER;
}

std::string Dacia::Graphics::Shader::ReadShader(std::string const & source)
{
	std::ifstream		file(source);
	std::stringstream	convertor;

	convertor<<file.rdbuf();
	return convertor.str();
}

template<typename T>
void Dacia::Graphics::Shader::SetParamater(std::string name, UniformType uniform, T value)
{
	switch (uniform)
	{
		case UNIFORM::BOOL		 : return m_shaderImpl->SetBool(name, value);
		case UNIFORM::INT 		 : return m_shaderImpl->SetInt(name, value)  ;
		case UNIFORM::UINT		 : return m_shaderImpl->SetUint(name, value)  ;
		case UNIFORM::FLOAT		 : return m_shaderImpl->SetFloat(name, value)  ;
		case UNIFORM::DOUBLE	 : return m_shaderImpl->SetDouble(name, value);
		case UNIFORM::VEC2I 	 : return m_shaderImpl->SetVec2i(name, value)  ;
		case UNIFORM::VEC2U 	 : return m_shaderImpl->SetVec2u(name, value)  ;
		case UNIFORM::VEC2F		 : return m_shaderImpl->SetVec2f(name, value)  ;
		case UNIFORM::VEC3I		 : return m_shaderImpl->SetVec3i(name, value)  ;
		case UNIFORM::VEC3U		 : return m_shaderImpl->SetVec3u(name, value)  ;
		case UNIFORM::VEC3F 	 : return m_shaderImpl->SetVec3f(name, value)  ;
		case UNIFORM::VEC4I  	 : return m_shaderImpl->SetVec4i(name, value)  ;
		case UNIFORM::VEC4U  	 : return m_shaderImpl->SetVec4u(name, value)  ;
		case UNIFORM::VEC4F 	 : return m_shaderImpl->SetVec4f(name, value)  ;
		case UNIFORM::MAT2X2I  	 : return m_shaderImpl->SetMat2x2f(name, value)  ;
		case UNIFORM::MAT2X2U  	 : return m_shaderImpl->SetMat2x2f(name, value)  ;
		case UNIFORM::MAT2X2F 	 : return m_shaderImpl->SetMat2x2f(name, value)  ;
		case UNIFORM::MAT3X3I  	 : return m_shaderImpl->SetMat3x3i(name, value)  ;
		case UNIFORM::MAT3X3U  	 : return m_shaderImpl->SetMat3x3f(name, value)  ;
		case UNIFORM::MAT3X3F 	 : return m_shaderImpl->SetMat3x3f(name, value)  ;
		case UNIFORM::MAT4X4I  	 : return m_shaderImpl->SetMat4x4f(name, value)  ;
		case UNIFORM::MAT4X4U  	 : return m_shaderImpl->SetMat4x4f(name, value)  ;
		case UNIFORM::MAT4X4F 	 : return m_shaderImpl->SetMat4x4f(name, value)  ;
		case UNIFORM::SAMPLER1D  : return m_shaderImpl->SetSampler1d(name, value)  ;
		case UNIFORM::SAMPLER2D  : return m_shaderImpl->SetSampler2d(name, value)  ;
		case UNIFORM::SAMPLER3D	 : return m_shaderImpl->SetSampler3d(name, value)  ;
		
		default: return Log::Print(LOG::LOG_WARNING, "Invalid uniform type!");
	}
}

template<size_t size>
std::string Dacia::Graphics::Shader::ReadShader(char(&src)[size])
{
	std::ifstream file(src);
	std::stringstream convertor;
	
	convertor << file.rdbuf();
	return convertor.str();
}

template<size_t size>
std::string Dacia::Graphics::Shader::ReadShader(wchar_t(&src)[size])
{
	std::ifstream file(src);
	std::stringstream convertor;

	convertor << file.rdbuf();
	return convertor.str();
}

void Dacia::Graphics::ShaderImpl::PrintErrors()
{
	while (!m_errors.empty())
	{
		Log::Print(LOG::LOG_ERROR, "Shader error code: %d", m_errors.front());
		m_errors.pop();
	}
}
