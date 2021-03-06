
#include "precompiled.h"
#pragma hdrstop

#include "sys_engine.h"

btEngine engineGlobal = btEngine();
btTimer btEngine::m_mainTimer = btTimer();

btEngine::btEngine(void) : 
	m_state(GE_STARTING),	//we set to starting first
	m_frameHate(30)			//set 30, instead configuration set a diferent number
{
}

btEngine::~btEngine(void)
{
}

void btEngine::startUp(void)
{
	//create a free level to main menu
	m_level.EmptyLevel();
	gRendererGlobal.setupViewPort(800, 600);
	gRendererGlobal.startUp();
}

void btEngine::shutDown(void)
{
	//start clear the game level 
	m_level.clear();

	gRendererGlobal.shutDonw();
}

void btEngine::changeState(const Sint8 state)
{
	m_state = state;
}

const Sint8 btEngine::getState(void) const
{
	return m_state;
}

bool btEngine::sholdQuit(void) const
{
	return m_state == GE_QUIT;
}

void btEngine::thinkFrame(void)
{
	//game time management
	if (m_state == GE_PAUSED && !m_mainTimer.isPaused())
		m_mainTimer.pause();
	else if (m_state != GE_PAUSED && m_mainTimer.isPaused())
		m_mainTimer.unPause();

	//begin frame rendering, setup render enviroment
	gRendererGlobal.beginFrame();

	//update the main input
	//TODO: remove when create a input thread manager
	inputGlobal.updateInput();

	if (inputGlobal.getNumSystemInputs() > 0)
	{
		for (Uint32 i = 0; i < inputGlobal.getNumSystemInputs(); i++)
		{
			Uint32 signal = 0;
			inputGlobal.getSystemInputs(i, signal);

			//get the quit input signal
			if (signal == btSystemImput::SYS_QUIT)
				m_state = GE_QUIT;
		}
	}

	//update the game level
	m_level.update();

	//render meshes loop
	gRendererGlobal.renderBackend();

	//end frame rendering
	gRendererGlobal.endFrame();

	//frame control
	if (m_mainTimer.getTicks() < 1000 / m_frameHate)
	{
		//wait to sincronise
		SDL_Delay((1000 / m_frameHate) - m_mainTimer.getTicks());
	}

	//clear the stored input handlers
	inputGlobal.cleanInput();
}
