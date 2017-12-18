#include "ShaderOpenGL.hpp"
#include "OpenGL_Strings.hpp"


Dacia::uint32 Dacia::Graphics::OpenGL::ShaderImplOpenGL::UseDefault(GLenum type)
{
	std::string src = "";

	switch (type)
	{
		case GL_VERTEX_SHADER: src = GetDefaultShader(ShaderType::VERTEX);
			break;

		case GL_FRAGMENT_SHADER: src = GetDefaultShader(ShaderType::FRAGMENT);
			break;

		default: Log::Print(LOG::LOG_WARNING, "The specified type is either invalid or \
											   has a driver-implemented default version");
			return INVALID_SHADER;
	}

	return Compile(type, src);
}

Dacia::Graphics::OpenGL::ShaderImplOpenGL::ShaderImplOpenGL()
{
}

Dacia::uint32 Dacia::Graphics::OpenGL::ShaderImplOpenGL::Compile(GLenum type, std::string const & source)
{
	uint32 shader = glCreateShader(type);
	GetError();

	const GLchar * src = source.c_str();

	glShaderSource(shader, 1, &src, NULL);
	GetError();

	glCompileShader(shader);
	GetError();

	GLint status{ 0 };
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (!status)
	{
		GLchar buffer[Log::LOG_SIZE];
		glGetShaderInfoLog(shader, Log::LOG_SIZE, NULL, buffer);
		throw FailedCompilation(buffer);

		return INVALID_SHADER;
	}

	return shader;
}

Dacia::uint32 Dacia::Graphics::OpenGL::ShaderImplOpenGL::CompileShader(std::string vertex, std::string fragment, 
															   std::string tessellation, std::string control)
{
	bool useControl = true;
	if (control.empty())
	{
		Log::Print(LOG::LOG_WARNING, "Tessellation control shader is empty!");
		useControl = false;
	}

	if (tessellation.empty())
	{
		Log::Print(LOG::LOG_WARNING, "Tessellation evaluation shader is empty! \
									  Tessellation shaders won't be used.");
		
		return CompileShader(vertex, fragment);
	}


}

Dacia::uint32 Dacia::Graphics::OpenGL::ShaderImplOpenGL::CompileShader(std::string vertex,
															   std::string fragment, 
															   std::string optionalShader,
															   Dacia::Graphics::ShaderType type)
{
	if (optionalShader.empty())
		return CompileShader(vertex, fragment);

	GLenum openglShaderType;

	switch (type)
	{
		case Dacia::Graphics::ShaderType::GEOMETRY: 
			openglShaderType = GL_GEOMETRY_SHADER;
			break;

		case Dacia::Graphics::ShaderType::TESSELLATION_EVALUATION:
			openglShaderType = GL_TESS_EVALUATION_SHADER;
			break;

		default:
			Log::Print(LOG::LOG_WARNING, "Chosen shader type cannot be used as an optional shader!");
			return CompileShader(vertex, fragment);
	}

	uint32 m_shaderVertex = Compile(GL_VERTEX_SHADER, vertex); 
	GetError();

	if (m_shaderVertex == INVALID_SHADER)
		m_shaderVertex = UseDefault(GL_VERTEX_SHADER);

	uint32 m_shaderFragment	= Compile(GL_FRAGMENT_SHADER, fragment);
	GetError();

	if (m_shaderFragment == INVALID_SHADER)
		m_shaderFragment = UseDefault(GL_FRAGMENT_SHADER);

	uint32 m_shaderOptional= Compile(openglShaderType , optionalShader);
	GetError();

	m_shaderHandle.handle = glCreateProgram();

	glAttachShader(m_shaderHandle.handle, m_shaderVertex);
	GetError();

	glAttachShader(m_shaderHandle.handle, m_shaderFragment);
	GetError();

	glAttachShader(m_shaderHandle.handle, m_shaderOptional);
	GetError();

	glLinkProgram(m_shaderHandle.handle);
	GetError();

	GLint status{ 0 };
	glGetProgramiv(m_shaderHandle.handle, GL_LINK_STATUS, &status);

	glDeleteShader(m_shaderVertex);
	glDeleteShader(m_shaderFragment);
	glDeleteShader(m_shaderOptional);

	if (!status)
	{
		GLchar buffer[Log::LOG_SIZE];
		glGetProgramInfoLog(m_shaderHandle.handle, Log::LOG_SIZE, NULL, buffer);
		throw FailedLinkage(buffer);

		return INVALID_SHADER;
	}

	return m_shaderHandle.handle;
}

std::string Dacia::Graphics::OpenGL::ShaderImplOpenGL::GetDefaultShader(ShaderType shaderType)
{
	auto currentVersion = 
		DaciaEngine()->GetCurrentDriver()->GetCurrentVersion();

	Assert::Equal(currentVersion.first, DriverType::OPENGL);

	OpenGLVersion openGLVersion = OpenGLVersion(currentVersion.second);

	switch (shaderType)
	{
		case ShaderType::VERTEX:
			return openGLVersion < OpenGLVersion::OPENGL_33 ?
				 k_defaultVertexShaderVersion2 :
				 k_defaultVertexShaderVersion3Plus;
		
		case ShaderType::FRAGMENT:
			return openGLVersion < OpenGLVersion::OPENGL_33 ?
				k_defaultFragmentShaderVersion2 :
				k_defaultFragmentShaderVersion3Plus;
		
		default:
			Log::Print(LOG::LOG_ERROR, "The chosen shader type has no default!");
	}
}

Dacia::uint32 Dacia::Graphics::OpenGL::ShaderImplOpenGL::CompileShader(std::string vertex, std::string fragment)
{
	uint32 m_shaderVertex	= Compile(GL_VERTEX_SHADER, vertex);
	GetError();

	if (m_shaderVertex == INVALID_SHADER)
		m_shaderVertex = UseDefault(GL_VERTEX_SHADER);

	uint32 m_shaderFragment = Compile(GL_FRAGMENT_SHADER, fragment);
	GetError();

	if (m_shaderFragment == INVALID_SHADER)
		m_shaderFragment = UseDefault(GL_FRAGMENT_SHADER);


	m_shaderHandle.handle = glCreateProgram();
	GetError();

	glAttachShader(m_shaderHandle.handle, m_shaderVertex);
	GetError();

	glAttachShader(m_shaderHandle.handle, m_shaderFragment);
	GetError();

	glLinkProgram(m_shaderHandle.handle);
	GetError();

	GLint status{ 0 };
	glGetProgramiv(m_shaderHandle.handle, GL_LINK_STATUS, &status);

	glDeleteShader(m_shaderVertex);
	glDeleteShader(m_shaderFragment);

	if (!status)
	{
		GLchar buffer[Log::LOG_SIZE];
		glGetProgramInfoLog(m_shaderHandle.handle, Log::LOG_SIZE, NULL, buffer);

		throw FailedLinkage(buffer);
		return INVALID_SHADER;
	}

	return m_shaderHandle.handle;
}

Dacia::uint32 Dacia::Graphics::OpenGL::ShaderImplOpenGL::CompileShader(std::string vertex, 
															   std::string fragment, 
															   std::string geometry, 
															   std::string tessellation, 
															   std::string control)
{
	if (vertex.empty() || fragment.empty()) //if either vertex or fragment is empty, discard the rest and use defaults
			return CompileShader(vertex, fragment);

	if (geometry.empty() &&
		tessellation.empty() &&
		control.empty())
			return CompileShader(vertex, geometry);
	
	if (geometry.empty() &&
		!tessellation.empty() &&
		!control.empty())
			return CompileShader(vertex, fragment, tessellation, control);

	if (geometry.empty() ||
		tessellation.empty() ||
		control.empty())
	{
		if (!geometry.empty() && 
			tessellation.empty() && 
			control.empty())
				return CompileShader(vertex, fragment, geometry, ShaderType::GEOMETRY);

		if (tessellation.empty() && !control.empty())
				return CompileShader(vertex, fragment, geometry, ShaderType::TESSELLATION_CONTROL);
		else
				return CompileShader(vertex, fragment);
	}

	bool failGuard = false;

	uint32 shaderVertex = Compile(GL_VERTEX_SHADER, vertex);
	GetError();

	uint32 shaderFragment = Compile(GL_FRAGMENT_SHADER, fragment);
	GetError();

	if (shaderVertex == INVALID_SHADER || 
		shaderFragment == INVALID_SHADER)
	{
		failGuard = true;
		shaderVertex	= Compile(GL_VERTEX_SHADER, GetDefaultShader(ShaderType::VERTEX));
		shaderFragment	= Compile(GL_FRAGMENT_SHADER, GetDefaultShader(ShaderType::FRAGMENT));
	}

	m_shaderHandle.handle = glCreateProgram();
	GetError();

	glAttachShader(m_shaderHandle.handle, shaderVertex);
	GetError();

	glAttachShader(m_shaderHandle.handle, shaderFragment);
	GetError();

	uint32 shaderGeometry		= INVALID_SHADER;
	uint32 shaderTessellation	= INVALID_SHADER;
	uint32 shaderControl		= INVALID_SHADER;

	if (!failGuard)
	{
		shaderGeometry		= Compile(GL_GEOMETRY_SHADER, geometry);
		GetError();

		shaderTessellation	= Compile(GL_TESS_EVALUATION_SHADER, tessellation);
		GetError();

		shaderControl		= Compile(GL_TESS_CONTROL_OUTPUT_VERTICES, control);
		GetError();

		glAttachShader(m_shaderHandle.handle, shaderGeometry);
		GetError();

		glAttachShader(m_shaderHandle.handle, shaderTessellation);
		GetError();

		glAttachShader(m_shaderHandle.handle, shaderControl);
		GetError();
	}

	glLinkProgram(m_shaderHandle.id);
	GetError();

	GLint status{ 0 };
	glGetProgramiv(m_shaderHandle.handle, GL_LINK_STATUS, &status);

	glDeleteShader(shaderVertex);
	glDeleteShader(shaderFragment);

	if (!failGuard)
	{
		glDeleteShader(shaderGeometry);
		glDeleteShader(shaderTessellation);
		glDeleteShader(shaderControl);
	}

	if (!status)
	{
		GLchar buffer[Log::LOG_SIZE];
		glGetProgramInfoLog(m_shaderHandle.handle, Log::LOG_SIZE, NULL, buffer);

		throw FailedLinkage(buffer);
		return INVALID_SHADER;
	}

	return m_shaderHandle.handle;
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::GetError()
{
	int32 errorCode = -1;

	while ((errorCode=glGetError()) != GL_NO_ERROR)
		m_errors.push(ErrorTranslator(errorCode));
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::UseShader()
{
	glUseProgram(m_shaderHandle.handle);
	GetError();
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::RegisterShader()
{
	DaciaEngine()->GetMemoryTracker()->SignalObjectCreation
										(GPUObjectType::SHADER_PROGRAM,
										m_sizeInBytes,
										(void*)m_binaryData.c_str());
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::UnregisterShader()
{
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::CleanUp()
{
	glDeleteProgram(m_shaderHandle.handle);
}

Dacia::uint64 Dacia::Graphics::OpenGL::ShaderImplOpenGL::GetProgramSizeInBytes()
{
	
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::AddFlag(ShaderType, std::string flagName, std::string & shaderSource)
{
	if (!(flagName.empty() && shaderSource.empty()))
	{
		std::for_each(flagName.begin(), flagName.end(),
						[](char & c)
						{ c = toupper(c); });

		if(shaderSource.find(flagName)!=std::string::npos)
			return;		
		
		size_t position = 0;
		if (shaderSource.find("#version") != std::string::npos)
			position = shaderSource.find_first_of('\n') + 1;

		shaderSource.insert(position, std::string("#define") + char(0x20) + flagName + '\n');
	}
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVersion(byte versionID, std::string & shaderSource)
{
	auto firstNewLine	= shaderSource.find_first_of('\n');
	auto versionString	= k_versionStrings.find(OpenGLVersion(versionID));

	if (versionString == k_versionStrings.end())
		Log::Print(LOG::LOG_WARNING, "Invalid OpenGL version");

	if (shaderSource.substr(0, firstNewLine).find("#version") == std::string::npos)
	{
		if (shaderSource.find("#version") != std::string::npos)
		{
			Log::Print(LOG::LOG_WARNING, "The shader contains a version directive \
				                          that is not the first line of the program!");
			return;
		}

		shaderSource.insert(0, versionString->second + "\n");
	}
	else
	{
		Log::Print(LOG::LOG_DEBUG, "Replacing the shader's existing version directive");
		
		shaderSource.erase(0, firstNewLine-1);
		shaderSource.insert(0, versionString->second);
	}
}

std::string Dacia::Graphics::OpenGL::ShaderImplOpenGL::GetShaderBinaryData(bool getBinary, const uint32 maxSize)
{
	if (!m_isCompiled)
	{
		Log::Print(LOG::LOG_WARNING, "Shader hasn't been compiled yet! \
									  Can't retrieve binary data");

		return "Shader not compiled: No data retrieved";
	}

	if (!m_binaryData.empty())
		return m_binaryData;

	char * buffer = new char[maxSize];
	GLsizei length;
	GLenum	binFormat;

	glGetProgramBinary(m_shaderHandle.handle, maxSize, &length, &binFormat, (void*)buffer);
	GetError();

	m_sizeInBytes = (size_t)length;

	m_binaryData = "Shader Info: \n";
	m_binaryData +=	"Size: " + std::to_string(length) + " bytes\n" +
					"Binary Format: " + std::to_string(binFormat);
	
	if (getBinary)
	{
		m_binaryData += "\n";
		m_binaryData += buffer;
	}

	delete[] buffer;

	return m_binaryData;
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetBool(std::string name, bool val)
{
	//if(m_uniforms.find() != m_uniforms.end())
	glUniform1i(glGetUniformLocation(m_shaderHandle.handle,name.c_str()),val);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetInt(std::string name, const int32 & val)
{
	glUniform1i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), val);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetDouble(std::string name, const double & val)
{
	glUniform1d(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), val);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetFloat(std::string name, const float & val)
{
	glUniform1f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), val);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetUint(std::string name, const uint32 & val)
{
	glUniform1ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), val);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2i(std::string name, int32 x, int32 y)
{
	glUniform2i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2i(std::string name, std::array<int32, 2> vec2)
{
	glUniform2i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2[0], vec2[1]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2i(std::string name, int32 vec2[2])
{
	glUniform2i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2[0], vec2[1]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2i(std::string name, glm::i32vec2 vec2)
{
	glUniform2i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2.x, vec2.y);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2u(std::string name, uint32 x, uint32 y)
{
	glUniform2ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2u(std::string name, std::array<uint32, 2> vec2)
{
	glUniform2ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2[0], vec2[1]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2u(std::string name, uint32 vec2[2])
{
	glUniform2ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2[0], vec2[1]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2u(std::string name, glm::u32vec2 vec2)
{
	glUniform2ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2.x, vec2.y);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2f(std::string name, float x, float y)
{
	glUniform2f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2f(std::string name, std::array<float, 2> vec2)
{
	glUniform2f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2[0], vec2[1]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2f(std::string name, float vec2[2])
{
	glUniform2f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2[0], vec2[1]);
}


void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec2f(std::string name, glm::vec2 vec2)
{
	glUniform2f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec2.x, vec2.y);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3i(std::string name, int32 x, int32 y, int32 z)
{
	glUniform3i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y, z);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3i(std::string name, std::array<int32, 3> vec3)
{
	glUniform3i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3i(std::string name, int32 vec3[3])
{
	glUniform3i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3i(std::string name, glm::i32vec3 vec3)
{
	glUniform3i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3u(std::string name, uint32 x, uint32 y, uint32 z)
{
	glUniform3ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y, z);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3u(std::string name, std::array<uint32, 3> vec3)
{
	glUniform3ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3u(std::string name, uint32 vec3[3])
{
	glUniform3ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3u(std::string name, glm::u32vec2 vec3)
{
	glUniform3ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3f(std::string name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y, z);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3f(std::string name, std::array<float, 3> vec3)
{
	glUniform3f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3f(std::string name, float vec3[3])
{
	glUniform3f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec3f(std::string name, glm::u32vec2 vec3)
{
	glUniform3i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec3[0], vec3[1], vec3[2]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4i(std::string name, int32 x, int32 y, int32 z, int32 w)
{
	glUniform4i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y, z, w);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4i(std::string name, std::array<int32, 4> vec4)
{
	glUniform4i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4i(std::string name, int32 vec4[4])
{
	glUniform4i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4i(std::string name, glm::i32vec4 vec4)
{
	glUniform4i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4u(std::string name, uint32 x, uint32 y, uint32 z, uint32 w)
{
	glUniform4ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y, z, w);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4u(std::string name, std::array<uint32, 3> vec4)
{
	glUniform4ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4u(std::string name, uint32 vec4[3])
{
	glUniform4ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4u(std::string name, glm::u32vec2 vec4)
{
	glUniform4ui(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4f(std::string name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), x, y, z, w);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4f(std::string name, std::array<float, 3> vec4)
{
	glUniform4f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4f(std::string name, float vec4[4])
{
	glUniform4f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetVec4f(std::string name, glm::vec4 vec4)
{
	glUniform4f(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), vec4[0], vec4[1], vec4[2], vec4[3]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat2x2f(std::string name, std::array<float, 4> mat2x2)
{
	glUniformMatrix2fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, mat2x2.data());
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat2x2f(std::string name, float mat2x2[4])
{
	glUniformMatrix2fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, mat2x2);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat2x2f(std::string name, float mat2x2[2][2])
{
	glUniformMatrix2fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, &mat2x2[0][0]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat2x2f(std::string name, glm::mat2 const & mat2x2)
{
	glUniformMatrix2fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, &mat2x2[0][0]);
}


void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat3x3f(std::string name, std::array<float, 9> mat3x3)
{
	glUniformMatrix3fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, mat3x3.data());
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat3x3f(std::string name, float mat3x3[9])
{
	glUniformMatrix3fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, mat3x3);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat3x3f(std::string name, float mat3x3[3][3])
{
	glUniformMatrix3fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, &mat3x3[0][0]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat3x3f(std::string name, glm::mat3 const & mat3x3)
{
	glUniformMatrix3fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, &mat3x3[0][0]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat4x4f(std::string name, std::array<float, 16> mat4x4)
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, mat4x4.data());
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat4x4f(std::string name, float mat4x4[16])
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, &mat4x4[0]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat4x4f(std::string name, float mat4x4[4][4])
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, &mat4x4[0][0]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetMat4x4f(std::string name, glm::mat4 const & mat4x4)
{
	glUniformMatrix4fv(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), 1, GL_FALSE, &mat4x4[0][0]);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetSampler1d(std::string name, uint32 id)
{
	glUniform1i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()),id);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetSampler2d(std::string name, uint32 id)
{
	glUniform1i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), id);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetSampler3d(std::string name, uint32 id)
{
	glUniform1i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), id);
}

void Dacia::Graphics::OpenGL::ShaderImplOpenGL::SetCubemap(std::string name, uint32 id)
{
	glUniform1i(glGetUniformLocation(m_shaderHandle.handle, name.c_str()), id);
}
