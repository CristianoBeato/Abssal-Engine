
#include "precompiled.h"
#pragma hdrstop

#include "in_handler.h"

btInputManager	inputGlobal = btInputManager();

btInputManager::btInputManager(void)
{
}

btInputManager::~btInputManager(void)
{
}

void btInputManager::updateInput(void)
{
	void * input = static_cast<void*>(this);
	getInputs(input);
}

void btInputManager::cleanInput(void)
{
	//
	btMutexLock autolock(&m_inputMutex);

	m_mouse.clear();
	m_keyboard.clear();
	m_controler.clear();
	m_system.clear();
}

Uint32 btInputManager::getNumMouseInputs(void)
{
	btMutexLock autolock(&m_inputMutex);
	return m_mouse.size();
}

void btInputManager::getMouseAction(const Uint32 input, btMouseInput & handler)
{
	btMutexLock autolock(&m_inputMutex);
	SDL_assert(!(m_mouse.size() < input));
	handler = m_mouse[input];
}

void btInputManager::getMouseInput(const Uint32 input, int & key)
{
}

Uint32 btInputManager::getNumKeyboardInputs(void)
{
	btMutexLock autolock(&m_inputMutex);
	return m_keyboard.size();
}

Uint32 btInputManager::getNumControlerInputs(void)
{
	btMutexLock autolock(&m_inputMutex);
	return m_controler.size();
}

Uint32 btInputManager::getNumSystemInputs(void)
{
	btMutexLock autolock(&m_inputMutex);
	return m_system.size();
}

void btInputManager::getSystemInputs(Uint32 intput, Uint32 &handller)
{
	btMutexLock autolock(&m_inputMutex);
	SDL_assert(!(m_system.size() < intput));
	handller = m_system[intput].m_state;
}

void btInputManager::getInputs(void * ptr)
{
	SDL_Event Event;
	btInputManager* input = static_cast<btInputManager*>(ptr);
	btMutexLock autolock(&input->m_inputMutex);

	//TODO: Change SDL_PollEvent, to wait envent when implement threads 
	//Handle events on queue
	while (SDL_PollEvent(&Event) != 0)
	{
		if (Event.type == SDL_QUIT || Event.type == SDL_APP_TERMINATING)
		{
			input->m_system.push_back(btSystemImput(btSystemImput::SYS_QUIT, true));
		}
		else if (Event.type == SDL_APP_DIDENTERBACKGROUND)
		{
			input->m_system.push_back(btSystemImput(btSystemImput::SYS_ENVIROMENT_PAUSE, true));
		}
		else if (Event.type == SDL_APP_DIDENTERFOREGROUND)
		{
			input->m_system.push_back(btSystemImput(btSystemImput::SYS_ENVIROMENT_PAUSE, false));
		}
		else if (Event.type == SDL_WINDOWEVENT)
		{
			SDL_WindowEvent WinEvent = Event.window;
			switch (WinEvent.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				input->m_system.push_back(btSystemImput(btSystemImput::SYS_QUIT, true));
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
			case SDL_WINDOWEVENT_RESTORED:
			case SDL_WINDOWEVENT_RESIZED:
				input->m_system.push_back(btSystemImput(btSystemImput::SYS_VIEW_RESIZE, true));
				break;
			//pause game when minimised
			case SDL_WINDOWEVENT_MINIMIZED:
				input->m_system.push_back(btSystemImput(btSystemImput::SYS_ENVIROMENT_PAUSE, true));
				break;
			default:
				break;
			}
		}
		else if (Event.type == SDL_KEYDOWN)
		{
		}
		else if (Event.type == SDL_KEYUP)
		{
		}
		else if (Event.type == SDL_TEXTINPUT)
		{
		}
		else if (Event.type == SDL_MOUSEMOTION)
		{
			SDL_MouseMotionEvent MseEvent = Event.motion;
			//append the mouse moction 
			input->m_mouse.push_back(btMouseInput(MseEvent.x, MseEvent.y));
		}
		else if (Event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_MouseButtonEvent MseBteEvent = Event.button;
			switch (MseBteEvent.button)
			{
			case SDL_BUTTON_LEFT:
				input->m_mouse.push_back(btMouseInput(btMouseInput::MSE_BUTTON_LEFT, btImputHandler::INPUT_PRESS));
				break;
			case SDL_BUTTON_MIDDLE:
				input->m_mouse.push_back(btMouseInput(btMouseInput::MSE_BUTTON_CENTER, btImputHandler::INPUT_PRESS));
				break;
			case SDL_BUTTON_RIGHT:
				input->m_mouse.push_back(btMouseInput(btMouseInput::MSE_BUTTON_RIGHT, btImputHandler::INPUT_PRESS));
				break;
			default:
				break;
			}
		}
		else if (Event.type == SDL_MOUSEBUTTONUP)
		{
			SDL_MouseButtonEvent MseBteEvent = Event.button;
			switch (MseBteEvent.button)
			{
			case SDL_BUTTON_LEFT:
				input->m_mouse.push_back(btMouseInput(btMouseInput::MSE_BUTTON_LEFT, btImputHandler::IMPUT_RELEASE));
				break;
			case SDL_BUTTON_MIDDLE:
				input->m_mouse.push_back(btMouseInput(btMouseInput::MSE_BUTTON_CENTER, btImputHandler::IMPUT_RELEASE));
				break;
			case SDL_BUTTON_RIGHT:
				input->m_mouse.push_back(btMouseInput(btMouseInput::MSE_BUTTON_RIGHT, btImputHandler::IMPUT_RELEASE));
				break;
			default:
				break;
			}
		}
		else if (Event.type == SDL_MOUSEWHEEL)
		{
			SDL_MouseWheelEvent MseBteEvent = Event.wheel;
			input->m_mouse.push_back(btMouseInput(btMouseInput::MSE_WEEL, MseBteEvent.x));
		}
		else if (Event.type == SDL_CONTROLLERBUTTONUP)
		{
		}
		else if (Event.type == SDL_CONTROLLERBUTTONDOWN)
		{
		}
		else if (Event.type == SDL_CONTROLLERAXISMOTION)
		{
		}
	}
}
