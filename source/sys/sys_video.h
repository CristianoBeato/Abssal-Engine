
#ifndef _SYS_VIDEO_H_
#define _SYS_VIDEO_H_

#include "framework/configuration.h"

class btVideoManager
{
public:
	btVideoManager(void);
	~btVideoManager(void);

	//start the windown manager 
	void	StartUp(void);

	//close game windown manager
	void	ShutDonw(void);

	//show swap render buffers
	void	PresentFrame(void);

	//update video changes
	void	UpdateVideo(void);

private:

	void	setupVideoState(void);
	void	setOpenGlAttributes(void);
	void	createWindow(void);
	void	destroyWindow(void);
	void	createRenderContext(void);
	void	freeRenderContext(void);

	bool							m_success;
	btConfiguration::videoConf_t	m_videoConf;
	//main window handler
	SDL_Window*						m_window;
	SDL_GLContext*					m_context;

	//int dispay number
	Uint32							m_displayCount, m_currDisplay;

};

extern btVideoManager videoManagerGlobal;

#endif // !_SYS_VIDEO_H_
