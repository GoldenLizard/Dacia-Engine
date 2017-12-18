#include "Application.hpp"

Application::Application(std::string const & name, 
						GLuint const & x, 
						GLuint const & y, 
						bool fullscreen):
	m_resolution(std::make_pair(x,y)),
	m_fullscreen(fullscreen),
	m_name(name)
{

}

Application::~Application()
{

}
