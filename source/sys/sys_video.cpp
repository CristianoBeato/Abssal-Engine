
#include "precompiled.h"
#pragma hdrstop

#include "sys_video.h"

btVideoManager videoManagerGlobal = btVideoManager();

btVideoManager::btVideoManager(void) : m_window(NULL), m_context(NULL)
{
}

btVideoManager::~btVideoManager(void)
{
}

void btVideoManager::StartUp(void)
{
	//get the video configuration from file
	setupVideoState();

	//
	setOpenGlAttributes();

	//setup the game windown
	createWindow();

	//setup the OpenGL Render Context
	createRenderContext();
}

void btVideoManager::ShutDonw(void)
{
	destroyWindow();
}

void btVideoManager::PresentFrame(void)
{
	//window check
	SDL_assert(m_window);

	//Update screen
	SDL_GL_SwapWindow(m_window);
}

void btVideoManager::UpdateVideo(void)
{
	//clean video
	freeRenderContext();
	destroyWindow();

	//rebuild video;
	createWindow();
	createRenderContext();
}

void btVideoManager::setupVideoState(void)
{
	SDL_DisplayMode mode;
	//list the avaidable displays
	m_displayCount = SDL_GetNumVideoDisplays();

	SDL_GetNumDisplayModes(m_currDisplay);
	SDL_GetCurrentDisplayMode(m_currDisplay, &mode);

	this->m_videoConf = configurationGlobal.getVideoConfig();

	//center the display
	if (m_videoConf.posX < 0)
		m_videoConf.posX = SDL_WINDOWPOS_CENTERED;
	if (m_videoConf.posY < 0)
		m_videoConf.posY = SDL_WINDOWPOS_CENTERED;
}

void btVideoManager::setOpenGlAttributes(void)
{
	//Use OpenGL 3.1 core
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	//development
	if (true)	//use OGL Core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	else   //compatibility
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	if (m_videoConf.doubleBuffer)
	{
		//Double buffer should be on by default, but I set it anyway
		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0)
			printf("Warning: Unable to set Double buffer VSync! SDL Error: %s\n", SDL_GetError());
	}
	else
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, m_videoConf.multisamples ? 1 : 0);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, m_videoConf.multisamples);
}

void btVideoManager::createWindow(void)
{
	m_success = false;

	//defalt sdl flags
	Uint32	sdlFlags = SDL_WINDOW_OPENGL;

	gConsole.printf("Creting game window:\n");

	//set full size window
	if (m_videoConf.mode < 1)
		sdlFlags |= SDL_WINDOW_FULLSCREEN;
	else
	{
		if (m_videoConf.mode > 1)
			sdlFlags |= SDL_WINDOW_BORDERLESS;
	}
	
	m_window = SDL_CreateWindow(GAME_NAME, 
		m_videoConf.posX, m_videoConf.posY, 
		m_videoConf.vidWidth, m_videoConf.vidHeight, 
		sdlFlags);

	if (!m_window)
	{
		gConsole.fatalError("can't start the video, can't create SDL Window, get SDL Err: %s.\n", SDL_GetError());
		return;
	}

	m_success = true;
	gConsole.printf("DONE\n");
}

void btVideoManager::destroyWindow(void)
{
	gConsole.printf("cleaning game window:\n");
	SDL_DestroyWindow(m_window);
	m_window = NULL; 
	gConsole.printf("done\n");
}

void btVideoManager::createRenderContext(void)
{
	if (!m_success)
		return;

	//window check
	SDL_assert(m_window);

	m_success = false;

	gConsole.printf("Creting game render context:\n");
	m_context = (SDL_GLContext*)SDL_malloc(sizeof(SDL_GLContext));
	//Create context
	*m_context = SDL_GL_CreateContext(m_window);
	if (m_context == NULL)
	{
		gConsole.error("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
		return;
	}

	//Initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		gConsole.error("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		return;
	}

	//Use Vsync
	if (m_videoConf.enableVsync)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
			printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}
	else
		SDL_GL_SetSwapInterval(0);

	m_success = true;
	gConsole.printf("DONE\n");
}

void btVideoManager::freeRenderContext(void)
{
	gConsole.printf("cleaning the render context:\n");
	SDL_free(m_context);
	m_context = NULL;
	gConsole.printf("done\n");
}
