#pragma once

#include "../Application.hpp"

class GLFWApp final :
	public Application
{
	struct WindowDestructor;

	public:

	 GLFWApp(std::string const & name, const GLuint & x, GLuint const & y, bool fullscreen = false);
	~GLFWApp();

	GLFWApp(const GLFWApp & other)					= delete;
	GLFWApp(GLFWApp && other)						= default;
	GLFWApp & operator=(const GLFWApp & other)		= delete;
	GLFWApp & operator=(GLFWApp && other)			= default;

	void virtual SetResolution(GLuint const & x, GLuint const & y) override;

	void virtual Init()		override;
	void virtual Update()	override;
	void virtual Destroy()	override;

	void virtual SetViewport() override;
	void virtual MakeCurrent() override;
	void virtual MakeWindow() override;

	GLfloat	GetDPI() const;

	virtual inline bool WindowShouldClose() const override
	{
		return glfwWindowShouldClose(m_window.get()) == 1 ? true : false;
	}

	void SetGLFWHints(std::pair<int, int> const & versions = { 4,4 },
		bool resizable = true,
		std::pair<bool, int> antialias = { true, 8 });

	void SetGamma(float const & gamma);
	void SetWindowedMode();
	void SetKeyCallback(void(*callback)(GLFWwindow*,int,int,int));

	GLFWmonitor * GetMonitor(GLuint const & no);
	std::unique_ptr<GLFWwindow,	 WindowDestructor>	GetWindow();

	static void OnError(int errorCode, char * error);

	private:

	void GetMonitors();

	struct WindowDestructor
	{
		void operator()(GLFWwindow * ptr)
		{
			glfwDestroyWindow(ptr);
		}
	};

	std::function<void(GLFWwindow*,int,int,int)> m_keyCallback;

	std::unique_ptr<GLFWwindow,	WindowDestructor>	m_window;
	std::vector<GLFWmonitor*>						m_monitors;
	
	static bool IsInit;
};