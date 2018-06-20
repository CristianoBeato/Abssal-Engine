
#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include <vector>

struct btImputHandler
{
	btImputHandler(void)
	{
		m_key = 0;
		m_state = 0;
		m_level = 0;
	}

	enum
	{
		IMPUT_FREE = 0, //the key is "idle"
		INPUT_PRESS,
		IMPUT_RELEASE,
	};

	int			m_key;
	int			m_state;
	Uint16		m_level;	//for analogic input in controlers
};

//Deal whit Mouse
struct btMouseInput : btImputHandler
{
	enum
	{
		MSE_MOTION = 0,
		MSE_WEEL,
		MSE_BUTTON_LEFT,
		MSE_BUTTON_CENTER,
		MSE_BUTTON_RIGHT,
	};

	btMouseInput(void) :btImputHandler()
	{
		moveX = 0.0f;
		moveY = 0.0f;
	}

	btMouseInput(int k, bool s)
	{
		m_key = k;
		m_state = s;
	}
	
	btMouseInput(float x, float y)
	{
		m_state = MSE_MOTION;
		moveX = x;
		moveY = y;
	}

	float moveX, moveY;
};

//Deal whit Keyboard Inputs
struct btKeyboardInput : btImputHandler
{
	btKeyboardInput(void) : btImputHandler()
	{
	}

	btKeyboardInput(int k, bool s)
	{
		m_key = k;
		m_state = s;
	}

};

//Deal Whit Joistic/controler inputs
struct btControlerInput : btImputHandler
{
	btControlerInput(void) : btImputHandler()
	{
	}

	btControlerInput(int k, bool s)
	{
		m_key = k;
		m_state = s;
	}

	btControlerInput(int k, Uint16 l)
	{
		m_key = k;
		m_level = l;
	}
};

//deal whit System inputs
struct btSystemImput : btImputHandler
{
	enum
	{
		SYS_ZERO = 0,
		SYS_QUIT,
		SYS_ENVIROMENT_PAUSE,	//pause when in background
		SYS_VIEW_RESIZE,
		//SYS_ENVIROMENT_UNPAUSE, //retur from background
		//window get the mouse focus 
	};

	btSystemImput(void) : btImputHandler()
	{
	}

	btSystemImput(int k, bool m)
	{
		m_key = k;
		m_state = m;
	}

};

class btInputManager
{
public:
	btInputManager(void);
	~btInputManager(void);

	void		updateInput(void);
	void		cleanInput(void);

	Uint32		getNumMouseInputs(void);
	void		getMouseAction(const Uint32 input, btMouseInput & handler);
	void		getMouseInput(const Uint32 input, int &key);
	
	Uint32		getNumKeyboardInputs(void);
	void		getKeyboarInput(const Uint32 intput, int &key);
	void		getTextKeyboardInput(const char * text);

	Uint32		getNumControlerInputs(void);
	void		getControlerInput(const Uint32 intput, int &key);
	void		setControlerRumbler(Uint8 intensity, Uint8 cicleSize);

	Uint32		getNumSystemInputs(void);
	void		getSystemInputs(const Uint32 intput, Uint32 &handller);

private:
	static void	getInputs(void* ptr);

	//imput handler mtex
	btMutex			m_inputMutex;
	//TODO: create a call for a worker thread here

	//store the system inputs
	std::vector<btMouseInput>		m_mouse;
	std::vector<btKeyboardInput>	m_keyboard;
	std::vector<btControlerInput>	m_controler;
	std::vector<btSystemImput>		m_system;
};

extern btInputManager	inputGlobal;

#endif // !_INPUT_HANDLER_H_
