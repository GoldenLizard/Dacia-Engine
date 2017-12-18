#include "GLFWApp.hpp"
#include <Utilities\Common.hpp>
#include <Utilities\EngineUtilities.hpp>

using namespace Dacia;

bool GLFWApp::IsInit = false;

GLFWApp::GLFWApp(std::string const & name, GLuint const & x, GLuint const & y, bool fullscreen):
	Application(name, x, y, fullscreen)
{

}

GLFWApp::~GLFWApp()
{
	Destroy();
}

void GLFWApp::SetResolution(GLuint const & x, GLuint const & y)
{
	m_resolution = std::make_pair(x, y);
	SetViewport();
}

void GLFWApp::Init()
{
	if (!IsInit)
	{
		IsInit = true;

		try
		{
			if (!glfwInit())
				Log::Print(LOG::LOG_ERROR, "Failed to initialize GLFW");

			glfwSetErrorCallback(GLFWerrorfun(OnError));

			SetGLFWHints();
			MakeWindow();
			MakeCurrent();

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				Log::Print(LOG::LOG_ERROR, "Failed to initialize GLAD");

			SetViewport();
		}
		catch (std::exception e)
		{
			Log::Print(LOG::LOG_ERROR, "%s", e.what());
		}
	}
	else
		Log::Print(LOG::LOG_WARNING, "A GLFW application has already been initialized!");
}

void GLFWApp::Update()
{
	glfwSwapBuffers(m_window.get());
	glfwPollEvents();
}

void GLFWApp::Destroy()
{
	m_window.reset();
	m_monitors.clear();

	glfwTerminate();
}

void GLFWApp::SetGLFWHints(	std::pair<int, int> const & versions,
							bool resizable,
							std::pair<bool, int> antialias)
{
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versions.first);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versions.second);

	glfwWindowHint(GLFW_RESIZABLE, resizable ? GL_TRUE : GL_FALSE);

	if (antialias.first)
		glfwWindowHint(GLFW_SAMPLES, antialias.second);

}

void GLFWApp::SetViewport()
{
	std::pair<int, int> fbSize;
	glfwGetFramebufferSize(m_window.get(), &fbSize.first, &fbSize.second);

	if (fbSize.first != m_resolution.first || fbSize.second != m_resolution.second)
	{
		Log::Print(LOG::LOG_GRAPHICS, "Current Resolution doesn't match framebuffer's size");
		m_resolution.first  = fbSize.first;
		m_resolution.second = fbSize.second;
	}

	Log::Print(LOG::LOG_DEBUG, "Setting Viewport");
	glViewport(0, 0, m_resolution.first, m_resolution.second);
}

void GLFWApp::MakeCurrent()
{
	if (m_window)
		glfwMakeContextCurrent(m_window.get());
}

void GLFWApp::MakeWindow()
{
	auto monitor = m_fullscreen ? glfwGetPrimaryMonitor() : nullptr;

	m_window = std::unique_ptr<GLFWwindow, WindowDestructor>(
				glfwCreateWindow(m_resolution.first, m_resolution.second,
				m_name.c_str(), monitor,
				nullptr));

	if (!m_window)
		throw InvalidWindow("Failed to initialize GLFW window!");
}

GLfloat GLFWApp::GetDPI() const
{
	return 0.f;
}

void GLFWApp::SetGamma(float const & gamma)
{
	for(auto monitor : m_monitors)
		glfwSetGamma(monitor, gamma);
}


void GLFWApp::SetWindowedMode()
{
}

void GLFWApp::SetKeyCallback(void(*callback)(GLFWwindow *, int, int, int))
{
	glfwSetKeyCallback(m_window.get(), GLFWkeyfun(callback));
}

GLFWmonitor * GLFWApp::GetMonitor(GLuint const & no)
{
	try
	{
		return m_monitors[no];
	}
	catch (std::out_of_range e)
	{
		Log::Print(LOG::LOG_ERROR, "Monitor %d doesn't exist!", no);
		return glfwGetPrimaryMonitor();
	}
}

std::unique_ptr<GLFWwindow, GLFWApp::WindowDestructor> GLFWApp::GetWindow()
{
	return std::unique_ptr<GLFWwindow, WindowDestructor>();
}

void GLFWApp::OnError(int errorCode, char * error)
{
	Log::Print(LOG::LOG_ERROR, "GLFW_ERROR[#%d] .%s!", errorCode, error);
}

void GLFWApp::GetMonitors()
{
	int * noMonitors = nullptr;
	auto monitorPtrs = glfwGetMonitors(noMonitors);

	Log::Print(LOG::LOG_DEBUG, "%d monitors detected", *noMonitors);
	m_monitors.resize(*noMonitors);

	m_monitors.insert(m_monitors.begin(), 
					  monitorPtrs, 
					  monitorPtrs + *noMonitors);
}


