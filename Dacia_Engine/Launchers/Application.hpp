#pragma once

#include <Utilities/Common.hpp>

class Application
{
	protected:

	struct InvalidWindow :
		public std::runtime_error
	{
		explicit InvalidWindow(const std::string & _Message) :
			std::runtime_error(_Message.c_str())
		{}

		explicit InvalidWindow(const char * _Message) :
			std::runtime_error(_Message)
		{}
	};

	public:

		Application(std::string const & name,
					GLuint const & x, 
					GLuint const & y, 
					bool fullscreen = false);

	   ~Application();

	   inline std::pair<GLuint, GLuint> getResolution() const
	   {
		   return m_resolution;
	   }

	   void virtual SetResolution(GLuint const & x, GLuint const & y) = 0;

	   void virtual Init()			= 0;
	   void virtual Update()		= 0;
	   void virtual Destroy()		= 0;

	   void virtual MakeWindow()  = 0;
	   void virtual SetViewport() = 0;
	   void virtual MakeCurrent() = 0;

	   virtual inline bool WindowShouldClose() const = 0;

	protected:

		std::pair<GLuint, GLuint>	m_resolution;
		bool						m_fullscreen;
		std::string					m_name;
		
};

typedef std::shared_ptr<Application> ApplicationPtr;